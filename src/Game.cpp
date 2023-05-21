
#include "Game.h"

Game::Game(sf::RenderWindow& game_window): window(game_window)
{
  srand(time(nullptr));
}

bool Game::init()
{
  game_data = std::make_shared<GameData>();
  game_data->current_state = StateEnum::MAIN_MENU;
  game_data->window = std::unique_ptr<sf::RenderWindow>(&window);
  game_data->font.loadFromFile("Data/Fonts/ARCADECLASSIC.TTF");


  game_data->map_filepaths.emplace_back();
  game_data->map_filepaths.back() = {"Data/TiledProject/map1.tmx",
                                  "Data/TiledProject/Dungeon_Tileset_TrueTopdown_Walls (Custom).png",
                                  "../Data/Images/Sprites/map_image1.png"};

  game_data->map_filepaths.emplace_back();
  game_data->map_filepaths.back() = {"Data/TiledProject/map2.tmx",
                                  "Data/TiledProject/Dungeon_Tileset_TrueTopdown_Walls (Custom).png",
                                  "../Data/Images/Sprites/map_image2.png"};


  game_data->normal_view.setSize(float(window.getSize().x), float(window.getSize().y));
  game_data->normal_view.setCenter(float(window.getSize().x)/2, float(window.getSize().y)/2);

  game_data->player_text.loadFromFile("Data/Images/Sprites/player (Custom).png");
  game_data->orange_enemy_text.loadFromFile("Data/Images/Sprites/orange (Custom).png");
  game_data->pink_enemy_text.loadFromFile("Data/Images/Sprites/pink (Custom).png");
  game_data->red_enemy_text.loadFromFile("Data/Images/Sprites/red (Custom).png");
  game_data->blue_enemy_text.loadFromFile("Data/Images/Sprites/blue (Custom).png");
  game_data->green_enemy_text.loadFromFile("Data/Images/Sprites/green (Custom).png");
  game_data->player_arrow.loadFromFile("Data/Images/Arrow.png");
  game_data->mushrooms_text.loadFromFile("Data/Images/Sprites/mushrooms(24x24 each).png");
  game_data->fleeing_texture.loadFromFile("Data/Images/Sprites/Fleeing (Custom).png");

  game_data->mushroom_sample_rects.reserve(3);
  for (int i = 0; i < 3; i++)
  {
    game_data->mushroom_sample_rects.emplace_back(sf::IntRect (i * 24, 0, 24, 24));
  }

  states.reserve(6);
  states.emplace_back(std::make_unique<MainMenu>(game_data));
  states.emplace_back(std::make_unique<MapSelectMenu>(game_data));
  states.emplace_back(std::make_unique<GamePlay>(game_data));
  states.emplace_back(std::make_unique<WinMenu>(game_data));
  states.emplace_back(std::make_unique<LoseMenu>(game_data));

  for (auto& state: states)
  {
    state->initState();
  }

  return true;
}

void Game::update(float dt)
{
  if (game_data->prep_next_state)
  {
    prepState();
  }
  states[(int)(game_data->current_state)]->update(dt);
}

void Game::render()
{
  states[(int)(game_data->current_state)]->render();
}

void Game::mouseClicked(sf::Event event)
{
  states[(int)(game_data->current_state)]->mouseClicked(event);
}

void Game::mouseMoved(sf::Event event)
{
  states[(int)(game_data->current_state)]->mouseMoved(event);
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  states[(int)(game_data->current_state)]->keyPressed(event);
}


void Game::prepState()
{
  states[(int)(game_data->current_state)]->prepState();
  game_data->prep_next_state = false;
}

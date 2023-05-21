//
// Created by Jade on 02/12/2022.
//

#include "MapSelectMenu.h"


MapSelectMenu::MapSelectMenu(std::shared_ptr<GameData> data) : State(data)
{
  selected_option = MapOptions::ORIGINAL;
}


void MapSelectMenu::initState()
{
  option_texts.reserve(2);
  title_text = sf::Text();
  option_texts.emplace_back();
  option_texts.emplace_back();


  Helper::textInit(
    title_text, "Choose A Map", game_data->font, game_data->orange, 60);
  Helper::textSetPosInWindow(
    title_text, *game_data->window, 0, -150);

  Helper::textInit(
    option_texts[(int)(MapOptions::ORIGINAL)], "ORIGINAL", game_data->font, game_data->orange, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(MapOptions::ORIGINAL)], *game_data->window, -150, 100);

  Helper::textInit(
    option_texts[(int)(MapOptions::OTHER)], "OTHER", game_data->font, game_data->grey, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(MapOptions::OTHER)], *game_data->window, 150, 100);


  if (background_text.loadFromFile("Data/Images/Sprites/map_image1.png") &&
    background_text2.loadFromFile("Data/Images/Sprites/map_image2.png"))
  {
    background.setTexture(background_text);
    background.setColor(sf::Color(255, 255, 255, 140));
    background.setPosition(game_data->normal_view.getCenter().x - background.getGlobalBounds().width/2, game_data->normal_view.getCenter().y - background.getGlobalBounds().height/2);
  }
}


void MapSelectMenu::render()
{
  game_data->window->setView(game_data->normal_view);
  game_data->window->draw(background);

  for (const auto& text : option_texts)
  {
    game_data->window->draw(text);
  }

  game_data->window->draw(title_text);
}


void MapSelectMenu::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*game_data->window);

    if (Collider::containsMouse(
          option_texts[(int)(MapOptions::ORIGINAL)].getGlobalBounds(),
          float(mouse_pos.x),
          float(mouse_pos.y)))
    {
      game_data->current_state = StateEnum::GAME_PLAY;
      game_data->prep_next_state = true;
      game_data->selected_map = (int)selected_option;
    }
    else if (Collider::containsMouse(
               option_texts[(int)(MapOptions::OTHER)].getGlobalBounds(),
               float(mouse_pos.x),
               float(mouse_pos.y)))
    {
      game_data->current_state = StateEnum::GAME_PLAY;
      game_data->prep_next_state = true;
      game_data->selected_map = (int)selected_option;
    }
  }
}


void MapSelectMenu::mouseMoved(sf::Event event)
{
  int x = -1;
  for (const auto& option : option_texts)
  {
    x++;

    if (Collider::containsMouse(option.getGlobalBounds(),
                                float(event.mouseMove.x),
                                float(event.mouseMove.y)))
    {
      selected_option = MapOptions(x);
      swapSelectionColours();
      break;
    }
  }
}


void MapSelectMenu::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter)
  {
    game_data->current_state   = StateEnum::GAME_PLAY;
    game_data->prep_next_state = true;
    game_data->selected_map    = (int)selected_option;
  }
  else if (event.key.code == sf::Keyboard::A)
  {
    selected_option = (MapOptions)std::clamp((int)(selected_option)-1, 0, (int)MapOptions::ENUMLENGTH-1);
    swapSelectionColours();
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    selected_option = (MapOptions)std::clamp((int)(selected_option)+1, 0, (int)MapOptions::ENUMLENGTH-1);
    swapSelectionColours();
  }
}

void MapSelectMenu::swapSelectionColours()
{
  for (auto& text : option_texts)
  {
    text.setFillColor(game_data->grey);
  }

  option_texts[(int)(selected_option)].setFillColor(game_data->orange);
  switch (selected_option)
  {
    case MapOptions::ORIGINAL:
    {
      background.setTexture(background_text);
      break;
    }
    case MapOptions::OTHER:
    {
      background.setTexture(background_text2);
      break;
    }
    default:
    {
      break;
    }
  }
}

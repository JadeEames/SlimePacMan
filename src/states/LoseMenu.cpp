//
// Created by Jade on 30/11/2022.
//

#include "LoseMenu.h"

LoseMenu::LoseMenu(std::shared_ptr<GameData> data) : State(data) {}

void LoseMenu::initState()
{
  selected_option = LoseMenuOptionsEnums::SCOREBOARD;

  main_text = sf::Text();
  score_text = sf::Text();

  option_texts.reserve(3);
  option_texts.emplace_back();
  option_texts.emplace_back();
  option_texts.emplace_back();

  Helper::textInit(main_text, "You Died!", game_data->font, game_data->orange, 60);
  Helper::textSetPosInWindow(main_text, *game_data->window, 0, -300);

  Helper::textInit(score_text, "Score:  ", game_data->font, game_data->orange, 60);

  Helper::textInit(
    option_texts[(int)(LoseMenuOptionsEnums::SCOREBOARD)], "Scoreboard", game_data->font, game_data->orange, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(LoseMenuOptionsEnums::SCOREBOARD)], *game_data->window, -280, 0);

  Helper::textInit(
    option_texts[(int)(LoseMenuOptionsEnums::REPLAY)], "Play Again", game_data->font, game_data->grey, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(LoseMenuOptionsEnums::REPLAY)], *game_data->window, 0, 0);

  Helper::textInit(
    option_texts[(int)(LoseMenuOptionsEnums::QUIT)], "Quit", game_data->font, game_data->grey, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(LoseMenuOptionsEnums::QUIT)], *game_data->window, 280, 0);

  background_text.loadFromFile("Data/Images/MenuLose.png");
  background.setTexture(background_text);
}

void LoseMenu::render()
{
  game_data->window->setView(game_data->normal_view);
  game_data->window->draw(background);

  for (const auto& text : option_texts)
  {
    game_data->window->draw(text);
  }

  game_data->window->draw(main_text);
  game_data->window->draw(score_text);
}

void LoseMenu::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*game_data->window);

    if (Collider::containsMouse(
          option_texts[(int)LoseMenuOptionsEnums::SCOREBOARD].getGlobalBounds(),
          float(mouse_pos.x),
          float(mouse_pos.y)))
    {
      game_data->current_state = StateEnum::SCORE_PAGE;
      game_data->prep_next_state = true;

    }
    else if (Collider::containsMouse(
               option_texts[(int)(LoseMenuOptionsEnums::REPLAY)].getGlobalBounds(),
               float(mouse_pos.x),
               float(mouse_pos.y)))
    {
      game_data->current_state = StateEnum::MAIN_MENU;
      game_data->prep_next_state = true;

    }
    else if (Collider::containsMouse(
               option_texts[(int)(LoseMenuOptionsEnums::QUIT)].getGlobalBounds(),
               float(mouse_pos.x),
               float(mouse_pos.y)))
    {
      game_data->window->close();
    }
  }
}

void LoseMenu::mouseMoved(sf::Event event)
{
  int x = -1;
  for (const auto& option : option_texts)
  {
    x++;

    if (Collider::containsMouse(option.getGlobalBounds(),
                                float(event.mouseMove.x),
                                float(event.mouseMove.y)))
    {
      selected_option = LoseMenuOptionsEnums(x);
      swapSelectionColours();
      break;
    }
  }
}

void LoseMenu::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter)
  {
    switch (selected_option)
    {
      case LoseMenuOptionsEnums::
      SCOREBOARD:
      {
        game_data->current_state   = StateEnum::SCORE_PAGE;
        game_data->prep_next_state = true;

        break;
      }
      case LoseMenuOptionsEnums::REPLAY:
      {
        game_data->current_state   = StateEnum::MAIN_MENU;
        game_data->prep_next_state = true;

        break;
      }

      case LoseMenuOptionsEnums::QUIT:
      {
        game_data->window->close();

        break;
      }

      default:
      {
        break;
      }
    }
  }
  else if (event.key.code == sf::Keyboard::A)
  {
    selected_option = (LoseMenuOptionsEnums)std::clamp(
      (int)(selected_option)-1, 0, (int)LoseMenuOptionsEnums::ENUMLENGTH - 1);
    swapSelectionColours();
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    selected_option = (LoseMenuOptionsEnums)std::clamp(
      (int)(selected_option) + 1, 0, (int)LoseMenuOptionsEnums::ENUMLENGTH - 1);
    swapSelectionColours();
  }
}

void LoseMenu::prepState()
{
  score_text.setString("Score:  " + std::to_string(game_data->score));
  Helper::textSetPosInWindow(score_text, *game_data->window, 0, -150);
}

void LoseMenu::swapSelectionColours()
{
  for (auto& text : option_texts)
  {
    text.setFillColor(game_data->grey);
  }

  option_texts[(int)(selected_option)].setFillColor(game_data->orange);
}

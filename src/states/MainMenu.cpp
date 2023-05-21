//
// Created by Jade on 08/11/2022.
//

#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<GameData> data) : State(data)
{
  selected_option = OptionEnums::PLAY;
}


void MainMenu::initState()
{
  option_texts.reserve(2);
  title_text = sf::Text();
  option_texts.emplace_back();
  option_texts.emplace_back();


  Helper::textInit(
    title_text, "Slime", game_data->font, game_data->orange, 60);
  Helper::textSetPosInWindow(
    title_text, *game_data->window, 0, -150);

  Helper::textInit(
    option_texts[(int)(OptionEnums::PLAY)], "PLAY", game_data->font, game_data->orange, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(OptionEnums::PLAY)], *game_data->window, -150, 100);

  Helper::textInit(
    option_texts[(int)(OptionEnums::QUIT)], "QUIT", game_data->font, game_data->grey, 40);
  Helper::textSetPosInWindow(
    option_texts[(int)(OptionEnums::QUIT)], *game_data->window, 150, 100);

  background_text.loadFromFile("Data/Images/Menu.png");
  background.setTexture(background_text);
}


void MainMenu::render()
{
  game_data->window->setView(game_data->normal_view);
  game_data->window->draw(background);

  for (const auto& text : option_texts)
  {
    game_data->window->draw(text);
  }

  game_data->window->draw(title_text);
}


void MainMenu::mouseClicked(sf::Event event)
{
  if (event.mouseButton.button == sf::Mouse::Left)
  {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*game_data->window);

    if (Collider::containsMouse(
          option_texts[(int)(OptionEnums::PLAY)].getGlobalBounds(),
          float(mouse_pos.x),
          float(mouse_pos.y)))
    {
      game_data->current_state = StateEnum::MAP_SELECTION_MENU;
      game_data->prep_next_state = true;
    }
    else if (Collider::containsMouse(
               option_texts[(int)(OptionEnums::QUIT)].getGlobalBounds(),
               float(mouse_pos.x),
               float(mouse_pos.y)))
    {
      game_data->window->close();
    }
  }
}


void MainMenu::mouseMoved(sf::Event event)
{
  int x = -1;
  for (const auto& option : option_texts)
  {
    x++;

    if (Collider::containsMouse(option.getGlobalBounds(),
          float(event.mouseMove.x),
          float(event.mouseMove.y)))
    {
      selected_option = OptionEnums(x);
      swapSelectionColours();
      break;
    }
  }
}


void MainMenu::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter)
  {
    switch (selected_option)
    {
      case OptionEnums::PLAY:
      {
        game_data->current_state = StateEnum::MAP_SELECTION_MENU;
        game_data->prep_next_state = true;
        break;
      }

      case OptionEnums::QUIT:
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
    selected_option = (OptionEnums)std::clamp((int)(selected_option)-1, 0, (int)OptionEnums::ENUMLENGTH-1);
    swapSelectionColours();
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    selected_option = (OptionEnums)std::clamp((int)(selected_option)+1, 0, (int)OptionEnums::ENUMLENGTH-1);
    swapSelectionColours();
  }
}


void MainMenu::swapSelectionColours()
{
  for (auto& text : option_texts)
  {
    text.setFillColor(game_data->grey);
  }

  option_texts[(int)(selected_option)].setFillColor(game_data->orange);
}

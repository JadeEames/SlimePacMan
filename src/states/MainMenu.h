//
// Created by Jade on 08/11/2022.
//

#pragma once

// This codebase
#include "State.h"
#include "../components/Helper.h"
#include "../components/Collider.h"

enum class OptionEnums : int
{
  PLAY = 0,
  QUIT = 1,
  ENUMLENGTH = 2
};

class MainMenu : public State
{
 public:
  explicit MainMenu(std::shared_ptr<GameData> data);
  ~MainMenu() = default;

  void initState() override;
  void render() override;

  void mouseClicked(sf::Event event) override;
  void mouseMoved(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void prepState() override {};

 private:
  OptionEnums selected_option;
  sf::Text title_text;
  std::vector<sf::Text> option_texts;

  void swapSelectionColours();
};

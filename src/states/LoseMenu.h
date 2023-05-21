//
// Created by Jade on 30/11/2022.
//

#pragma once

// This codebase
#include "State.h"
#include <iostream>

enum class LoseMenuOptionsEnums : int
{
  SCOREBOARD = 0,
  REPLAY = 1,
  QUIT = 2,
  ENUMLENGTH = 3
};

class LoseMenu : public State
{
 public:
  explicit LoseMenu(std::shared_ptr<GameData> data);
  ~LoseMenu() = default;

  void initState() override;
  void render() override;

  void mouseClicked(sf::Event event) override;
  void mouseMoved(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void prepState() override;

 private:
  LoseMenuOptionsEnums selected_option;
  sf::Text main_text;
  sf::Text score_text;
  std::vector<sf::Text> option_texts;

  void swapSelectionColours();
};


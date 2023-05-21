//
// Created by Jade on 21/11/2022.
//

#pragma once

// This codebase
#include "State.h"

enum class WinMenuOptionsEnums : int
{
  SCOREBOARD = 0,
  REPLAY = 1,
  QUIT = 2,
  ENUMLENGTH = 3
};

class WinMenu : public State
{
 public:
  explicit WinMenu(std::shared_ptr<GameData> data);
  ~WinMenu() = default;

  void initState() override;
  void render() override;

  void mouseClicked(sf::Event event) override;
  void mouseMoved(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void prepState() override;

 private:
  WinMenuOptionsEnums selected_option;
  sf::Text main_text;
  sf::Text score_text;
  std::vector<sf::Text> option_texts;

  void swapSelectionColours();
};

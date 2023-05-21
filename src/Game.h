
#pragma once

// Libraries
#include <iostream>
#include <SFML/Graphics.hpp>

// This codebase
#include "GameData.h"
#include "states/MainMenu.h"
#include "states/GamePlay.h"
#include "states/WinMenu.h"
#include "states/MapSelectMenu.h"
#include "states/LoseMenu.h"


class Game
{
 public:
  explicit Game(sf::RenderWindow& window);
  ~Game() = default;
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseMoved(sf::Event event);
  void keyPressed(sf::Event event);
  void prepState();

 private:
  sf::RenderWindow& window;
  std::shared_ptr<GameData> game_data = nullptr;
  std::vector<std::unique_ptr<State>> states;
};



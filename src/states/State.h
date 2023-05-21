//
// Created by Jade on 08/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

// This codebase
#include "../GameData.h"
#include "../components/Helper.h"
#include "../components/Collider.h"


class State
{
 public:
  explicit State(std::shared_ptr<GameData> data) {game_data.operator=(data);};
  ~State() = default;

  virtual void initState() {};
  virtual void update(float&) {};
  virtual void render() = 0;
  virtual void prepState() = 0;

  virtual void mouseClicked(sf::Event event) {};
  virtual void mouseMoved(sf::Event event) {};
  virtual void keyPressed(sf::Event event) {};
  //virtual void keyReleased(sf::Event event) {};

 protected:
  sf::Sprite background;
  sf::Texture background_text;
  std::shared_ptr<GameData> game_data = nullptr;
};

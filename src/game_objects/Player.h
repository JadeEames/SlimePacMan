//
// Created by Jade on 12/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

// This codebase
#include "Entity.h"

class Player : public Entity
{
 public:
  Player(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos);
  ~Player() = default;

  void update(float& dt) override;
  void spawn() override;
  void die() override;
  void render() override;
  void keyPressed(sf::Event event);

  int getLives() const;
  sf::Vector2i getDirection();
  void setHuntModeState(bool state);
  bool is_hunting = false;

 private:
  int lives = 0;
  const int max_lives = 3;

  sf::Sprite direction_arrow;
  sf::Vector2i current_direction;
  sf::Vector2i desired_direction = sf::Vector2i (0,-1);

  sf::Clock hunting_timer;
  float hunting_duration = 8;

  void resetPos(sf::Vector2i& current_tile_vec);
  void checkTileCollisions(float& dt);
  void setArrow();
};

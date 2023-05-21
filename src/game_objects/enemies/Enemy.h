//
// Created by Jade on 27/11/2022.
//

#pragma once

// This codebase
#include "../Entity.h"
#include "pathfinding/AStarPath.h"
#include "../Player.h"

class Enemy : public Entity
{
 public:
  Enemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos = sf::Vector2f(0,0));
  ~Enemy() = default;

  void update(float& dt) final {};
  virtual void move(float& dt);
  virtual void chasePathfind(Player& player, float& dt) = 0;
  virtual void fleePathfind(Player& player, float& dt);
  void die() override;
  void setFleeingTexture();
  void setDefaultTexture();

  bool is_path_empty();

  sf::Clock caged_timer;
  float caged_duration = 5;
  bool is_caged        = false;

  sf::Clock re_route_timer;
  float re_route_interval = 1;

  bool is_fleeing = false;

  sf::Clock dying_timer;
  float dying_duration = 0;
  bool is_dying = false;

  sf::Vector2f getTarget();

 protected:
  sf::Texture* default_texture;
  sf::Vector2f direction = {0,0};
  std::vector<sf::Vector2f> path;
  sf::Vector2f path_target = sf::Vector2f(0, 0);
};


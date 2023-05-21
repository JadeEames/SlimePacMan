//
// Created by Jade on 12/11/2022.
//

#pragma once

// This codebase
#include "../GameData.h"
#include "../components/Collider.h"
#include "../components/HitBoxSprite.h"
#include "../map/GameMap.h"

class Entity
{
 public:
  Entity(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos = sf::Vector2f(0,0));
  ~Entity() = default;

  virtual void update(float& dt) = 0;
  virtual void render();
  virtual void setPosition(sf::Vector2f& position);
  virtual void textureSprite(sf::Texture* texture);
  virtual void spawn();
  virtual void die() = 0;
  HitBoxSprite& getSprite();
  sf::Vector2f getMidPoint();

 protected:
  std::shared_ptr<GameData> game_data = nullptr;
  std::shared_ptr<GameMap> game_map = nullptr;
  std::shared_ptr<HitBoxSprite> sprite = nullptr;

  sf::Vector2f spawn_point;
  float speed = 200;
};

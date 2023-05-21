//
// Created by Jade on 03/12/2022.
//

#pragma once

#include "Enemy.h"

class BlueEnemy : public Enemy
{
 public:
  BlueEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos = sf::Vector2f(0,0));
  ~BlueEnemy() = default;

  void setBlinkyPinkyRefs(std::shared_ptr<Enemy>* blinky, std::shared_ptr<Enemy>* pinky);
  void chasePathfind(Player& player, float& dt) override;

 private:
  std::shared_ptr<Enemy> blinky_ptr;
  std::shared_ptr<Enemy> pinky_ptr;
};

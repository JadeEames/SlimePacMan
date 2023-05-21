//
// Created by Jade on 03/12/2022.
//

#pragma once

#include "Enemy.h"

class OrangeEnemy : public Enemy
{
 public:
  OrangeEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos = sf::Vector2f(0,0));
  ~OrangeEnemy() = default;

  void chasePathfind(Player& player, float& dt) override;
};

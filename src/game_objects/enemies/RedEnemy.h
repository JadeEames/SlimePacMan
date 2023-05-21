//
// Created by Jade on 21/11/2022.
//

#pragma once

#include "Enemy.h"

class RedEnemy : public Enemy
{
 public:
  RedEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos = sf::Vector2f(0,0));
  ~RedEnemy() = default;

  void chasePathfind(Player& player, float& dt) override;
};

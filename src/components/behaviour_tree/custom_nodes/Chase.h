//
// Created by Jade on 21/11/2022.
//

#pragma once

#include "../Node.h"

class Chase : public Node
{
 public:
  Chase() = default;
  ~Chase() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};



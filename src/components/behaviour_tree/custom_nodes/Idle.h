//
// Created by Jade on 28/11/2022.
//

#pragma once

#include "../Node.h"

class Idle : public Node
{
 public:
  Idle() = default;
  ~Idle() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};

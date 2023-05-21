//
// Created by Jade on 28/11/2022.
//

#pragma once

#include "../Node.h"

class Flee : public Node
{
 public:
   Flee() = default;
  ~Flee() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};

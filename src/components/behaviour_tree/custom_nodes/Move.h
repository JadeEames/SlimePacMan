//
// Created by Jade on 29/11/2022.
//

#pragma once

#include "../Node.h"

class Move : public Node
{
 public:
  Move() = default;
  ~Move() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};

//
// Created by Jade on 28/11/2022.
//

#pragma once

#include "../Node.h"

class Die : public Node
{
 public:
  Die() = default;
  ~Die() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};

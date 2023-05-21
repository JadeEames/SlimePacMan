//
// Created by Jade on 21/11/2022.
//

#pragma once

// This codebase
#include "Node.h"

class Sequence : public CompositeNode
{
 public:
  Sequence() = default;
  ~Sequence() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};


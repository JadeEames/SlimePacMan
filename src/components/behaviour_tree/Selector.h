//
// Created by Jade on 21/11/2022.
//

#pragma once

// This codebase
#include "Node.h"

class Selector : public CompositeNode
{
 public:
  Selector() = default;
  ~Selector() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;
};


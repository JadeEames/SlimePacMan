//
// Created by Jade on 21/11/2022.
//

#pragma once

#include "Node.h"

class InverterDecorator : public CompositeNode
{
 public:
  InverterDecorator() = default;
  ~InverterDecorator() = default;

  NodeStatus evaluate(Enemy& puppet, Player& player, float& dt) override;

 protected:
  Node* node;
};


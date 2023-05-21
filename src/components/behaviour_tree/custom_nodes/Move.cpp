//
// Created by Jade on 29/11/2022.
//

#include "Move.h"


NodeStatus Move::evaluate(Enemy& puppet, Player& player, float& dt)
{
  puppet.move(dt);
  return NodeStatus::SUCCESS;
}

//
// Created by Jade on 28/11/2022.
//

#include "Idle.h"

NodeStatus Idle::evaluate(Enemy& puppet, Player& player, float& dt)
{
  if (puppet.is_caged)
  {
    if (puppet.caged_timer.getElapsedTime().asSeconds() > puppet.caged_duration)
    {
      puppet.is_caged = false;
    }
  }
  return NodeStatus::FAILURE;
}

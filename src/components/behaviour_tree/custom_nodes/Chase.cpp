//
// Created by Jade on 21/11/2022.
//

#include "Chase.h"


NodeStatus Chase::evaluate(Enemy& puppet, Player& player, float& dt)
{
  if (!puppet.is_caged && !player.is_hunting)
  {
    if (puppet.re_route_timer.getElapsedTime().asSeconds() > puppet.re_route_interval || puppet.is_path_empty() || puppet.is_fleeing)
    {
      puppet.chasePathfind(player, dt);
      puppet.re_route_timer.restart();

      if (puppet.is_fleeing)
      {
        puppet.is_fleeing = false;
        puppet.setDefaultTexture();
      }

      return NodeStatus::SUCCESS;
    }
    return NodeStatus::RUNNING;
  }
  return NodeStatus::FAILURE;
}


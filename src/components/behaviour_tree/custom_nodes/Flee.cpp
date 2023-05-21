//
// Created by Jade on 28/11/2022.
//

#include "Flee.h"

NodeStatus Flee::evaluate(Enemy& puppet, Player& player, float& dt)
{
  if (player.is_hunting && !puppet.is_caged)
  {
    if (puppet.re_route_timer.getElapsedTime().asSeconds() > puppet.re_route_interval || puppet.is_path_empty() || !puppet.is_fleeing)
    {
      puppet.fleePathfind(player, dt);
      puppet.re_route_timer.restart();

      if (!puppet.is_fleeing)
      {
        puppet.is_fleeing = true;
        puppet.setFleeingTexture();
      }

      return NodeStatus::SUCCESS;
    }
    return NodeStatus::RUNNING;
  }
  return NodeStatus::FAILURE;
}

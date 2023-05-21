//
// Created by Jade on 21/11/2022.
//

#include "InverterDecorator.h"


NodeStatus InverterDecorator::evaluate(Enemy& puppet, Player& player, float& dt)
{
  switch (node->evaluate(puppet, player, dt))
  {
    case NodeStatus::SUCCESS:
    {
      node_status = NodeStatus::FAILURE;
      break;
    }
    case NodeStatus::FAILURE:
    {
      node_status = NodeStatus::SUCCESS;
      break;
    }
    case NodeStatus::RUNNING:
    {
      node_status = NodeStatus::RUNNING;
      break;
    }
  }

  return node_status;
}
//
// Created by Jade on 21/11/2022.
//

#include "Selector.h"


NodeStatus Selector::evaluate(Enemy& puppet, Player& player, float& dt)
{

  for (auto & node : nodes)
  {
    switch (node->evaluate(puppet, player, dt))
    {
      case NodeStatus::SUCCESS:
      {
        node_status = NodeStatus::SUCCESS;
        return node_status;
      }
      case NodeStatus::FAILURE:
      {
        break;
      }
      case NodeStatus::RUNNING:
      {
        node_status = NodeStatus::RUNNING;
        return node_status;
      }
    }
  }

  node_status = NodeStatus::FAILURE;
  return node_status;
}

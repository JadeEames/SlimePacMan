//
// Created by Jade on 21/11/2022.
//

#include "Sequence.h"

NodeStatus Sequence::evaluate(Enemy& puppet, Player& player, float& dt)
{
  bool anyChildRunning = false;

  for (auto & node : nodes)
  {
    switch (node->evaluate(puppet, player, dt))
    {
      case NodeStatus::SUCCESS:
      {
        break;
      }
      case NodeStatus::FAILURE:
      {
        node_status = NodeStatus::FAILURE;
        return node_status;
      }
      case NodeStatus::RUNNING:
      {
        anyChildRunning = true;
        break;
      }
    }
  }

  node_status = anyChildRunning ? NodeStatus::RUNNING : NodeStatus::SUCCESS;
  return node_status;
}

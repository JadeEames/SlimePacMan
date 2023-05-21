//
// Created by Jade on 28/11/2022.
//

#pragma once

// This codebase
#include <utility>

#include "Node.h"
#include "custom_nodes/Chase.h"
#include "custom_nodes/Flee.h"
#include "custom_nodes/Move.h"
#include "custom_nodes/Die.h"
#include "custom_nodes/Idle.h"
#include "Selector.h"
#include "Sequence.h"
#include "../../game_objects/enemies/Enemy.h"
#include "../../game_objects/Player.h"


class BehaviourTree
{
 public:
  explicit BehaviourTree(std::vector<std::shared_ptr<Enemy>>* enemies) : puppets(enemies)
  {
    root_selector       = std::make_unique<Selector>();
    chase_flee_selector = std::make_shared<Selector>();
    die_caged_selector  = std::make_shared<Selector>();

    pathfind_move_sequence = std::make_shared<Sequence>();
    chase = std::make_shared<Chase>();
    flee  = std::make_shared<Flee>();
    move = std::make_shared<Move>();

    die  = std::make_shared<Die>();
    idle = std::make_shared<Idle>();

    root_selector->addChild(pathfind_move_sequence);
    root_selector->addChild(die_caged_selector);

    pathfind_move_sequence->addChild(chase_flee_selector);
    pathfind_move_sequence->addChild(move);

    chase_flee_selector->addChild(chase);
    chase_flee_selector->addChild(flee);

    die_caged_selector->addChild(die);
    die_caged_selector->addChild(idle);
  };
  ~BehaviourTree() = default;

  void tick(Player& player, float& dt)
  {
    for (auto& puppet : *puppets)
    {
      root_selector->evaluate(*puppet, player, dt);
    }
  }

 private:
  std::vector<std::shared_ptr<Enemy>>* puppets;
  std::unique_ptr<Selector> root_selector;

  std::shared_ptr<Sequence> pathfind_move_sequence;
  std::shared_ptr<Selector> chase_flee_selector;
  std::shared_ptr<Chase> chase;
  std::shared_ptr<Flee> flee;
  std::shared_ptr<Move> move;

  std::shared_ptr<Selector> die_caged_selector;
  std::shared_ptr<Die> die;
  std::shared_ptr<Idle> idle;
};



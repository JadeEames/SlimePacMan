//
// Created by Jade on 21/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>
#include <memory>

// This codebase
#include "../../game_objects/enemies/Enemy.h"
#include "../../game_objects/Player.h"

enum class NodeStatus : int
{
  SUCCESS = 1,
  FAILURE = 2,
  RUNNING = 3
};


class Node
{
 public:
  Node() = default;
  ~Node() = default;

  NodeStatus getNodeStatus() { return node_status; };
  virtual NodeStatus evaluate(Enemy& puppet, Player& player, float& d) = 0;

 protected:
  NodeStatus node_status = NodeStatus::FAILURE;
};


class CompositeNode : public Node
{
 public:
  CompositeNode() = default;
  ~CompositeNode() = default;

  void addChild(std::shared_ptr<Node> child)
    {
      nodes.emplace_back(child);
    };

 protected:
  std::vector<std::shared_ptr<Node>> nodes;
};
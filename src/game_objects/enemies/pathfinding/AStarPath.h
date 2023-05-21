//
// Created by Jade on 25/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>
#include <queue>
#include <cmath>

// This codebase
#include "../../../map/GameMap.h"
#include "../../../GameData.h"


using TileLocation = std::tuple<int, int>;
using PriorityLocation = std::pair<int, TileLocation>;

namespace std {template <> struct hash<TileLocation>
  {
    std::size_t operator()(const TileLocation& id) const noexcept
    {
      return std::hash<int>()(std::get<0>(id) ^ (std::get<1>(id) << 16));
    }
  };
}

struct AStarPath
{
  static std::vector<sf::Vector2f> resolve(sf::Vector2f start_vect, sf::Vector2f target_vect, GameMap& map, GameData& data);

  static std::vector<sf::Vector2i> pathfind(TileLocation start_tile_vect, TileLocation target_tile_vect, GameMap& map, GameData& data);

  static std::vector<TileLocation> getNeighbours(TileLocation current_tile, GameMap& map, GameData& data);

  static int heuristic(TileLocation & destination, TileLocation & current_node);

  static std::vector<sf::Vector2i> construct_path(std::unordered_map<TileLocation, TileLocation> searched_route, TileLocation start_tile, TileLocation target_tile);

  static sf::Vector2f pathPointToDirection(sf::Vector2f& path, sf::Vector2f position);
};

//
// Created by Jade on 25/11/2022.
//

#include "AStarPath.h"

std::vector<sf::Vector2f> AStarPath::resolve(sf::Vector2f start_vect, sf::Vector2f target_vect, GameMap& map, GameData& data)
{
  sf::Vector2i start_tile = map.worldToTile(start_vect);
  sf::Vector2i target_tile = map.worldToTile(target_vect);
  int start_id = (int)data.floor->getTiles().at(map.indexTileByXY(start_tile)).ID;
  int target_id = (int)data.floor->getTiles().at(map.indexTileByXY(target_tile)).ID;

  std::vector<sf::Vector2i> tiles_to_visit;
  std::vector<sf::Vector2f> points_to_visit;
  tiles_to_visit.reserve(100);
  points_to_visit.reserve(100);

  if (start_id != 0 && target_id != 0 && start_vect != target_vect) // if both target & starting point are walkable tiles.
  {
    std::tuple<int, int> start_tile_tuple = std::make_tuple(start_tile.x, start_tile.y);
    std::tuple<int, int> target_tile_tuple = std::make_tuple(target_tile.x, target_tile.y);

    tiles_to_visit = pathfind(start_tile_tuple, target_tile_tuple, map, data);
    for (sf::Vector2i tile : tiles_to_visit)
    {
      points_to_visit.emplace_back(map.tileToWorld(tile));
    }
    std::reverse(points_to_visit.begin(), points_to_visit.end());
  }
  return points_to_visit;
}


std::vector<sf::Vector2i> AStarPath::pathfind(TileLocation start_tile_vect, TileLocation target_tile_vect, GameMap& map, GameData& data)
{
  std::priority_queue<PriorityLocation, std::vector<PriorityLocation>, std::greater<>> frontier;
  std::unordered_map<TileLocation, TileLocation> searched_route;
  std::unordered_map<TileLocation, int> steps_so_far;

  frontier.emplace(0, start_tile_vect);
  searched_route[start_tile_vect] = start_tile_vect;
  steps_so_far[start_tile_vect] = 0;

  while (!frontier.empty())
  {
    TileLocation current_tile = frontier.top().second;
    frontier.pop();

    if (current_tile == target_tile_vect)
    {
      break;
    }

    for (TileLocation next : getNeighbours(current_tile, map, data))
    {
      int step_cost = steps_so_far[current_tile] + 1;
      // don't actually use a cost map, so instead just add one.

      if (steps_so_far.find(next) == steps_so_far.end())
      {
        steps_so_far[next] = step_cost;
        int priority       = step_cost + heuristic(target_tile_vect, next);
        frontier.emplace(priority, next);
        searched_route[next] = current_tile;
      }
    }
  }

  return construct_path(searched_route, start_tile_vect, target_tile_vect);
}

std::vector<TileLocation>AStarPath::getNeighbours(TileLocation current_tile, GameMap& map, GameData& data)
{
  std::vector<TileLocation> neighbours;
  std::vector<TileLocation> offsets = {std::make_tuple(-1, 0), std::make_tuple(0, -1), std::make_tuple(1, 0), std::make_tuple(0, 1)};

  for (TileLocation offset : offsets)
  {
    // offset current tile to get adjacent tiles.
    TileLocation offset_tile = std::make_tuple(
      std::get<0>(current_tile) + std::get<0>(offset),
      std::get<1>(current_tile) + std::get<1>(offset));

    // make sure node is within map.
    if (
      std::get<0>(offset_tile) < 0 ||
      std::get<0>(offset_tile) > map.tmx_map->getTileCount().x - 1 ||
      std::get<1>(offset_tile) < 0 ||
      std::get<1>(offset_tile) > map.tmx_map->getTileCount().y - 1)
    {
      continue;
    }

    // checks whether the tile is walkable.
    if (data.floor->getTiles().at(map.indexTileByXY(sf::Vector2i(std::get<0>(offset_tile), std::get<1>(offset_tile)))).ID == 0)
    {
      continue;
    }

    neighbours.push_back(offset_tile);
  }

  return neighbours;
}


int AStarPath::heuristic(TileLocation& destination, TileLocation& current_node)
{
  return abs(std::get<0>(destination) - std::get<0>(current_node)) + abs(std::get<1>(destination) - std::get<1>(current_node));
}


std::vector<sf::Vector2i> AStarPath::construct_path(std::unordered_map<TileLocation, TileLocation> searched_route, TileLocation start_tile, TileLocation target_tile)
{
  TileLocation current = target_tile;
  std::vector<sf::Vector2i> path;

  while (current != start_tile && (std::get<0>(current) != 0 && std::get<1>(current) != 0))
  {
    path.emplace_back(std::get<0>(current), std::get<1>(current));
    current = searched_route[current];
    //        ^^ points to next path location.
    //           key  : location
    //        step 1 : step 2
    //        step 2 : step 3...
  }

  return path;
}


sf::Vector2f AStarPath::pathPointToDirection(sf::Vector2f& path, sf::Vector2f position)
{
  sf::Vector2f direction = {0, 0};

  direction.x = path.x - position.x;
  direction.y = path.y - position.y;

  float maginitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

  direction.x /= maginitude;
  direction.y /= maginitude;

  return direction;
}

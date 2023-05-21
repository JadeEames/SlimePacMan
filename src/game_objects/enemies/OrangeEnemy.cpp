//
// Created by Jade on 03/12/2022.
//

#include "OrangeEnemy.h"

OrangeEnemy::OrangeEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map,sf::Vector2f spawn_pos) : Enemy(data, map, spawn_pos)
{
  sprite->setTexture(data->orange_enemy_text);
  default_texture = &data->orange_enemy_text;
}


void OrangeEnemy::chasePathfind(Player& player, float& dt)
{
  if (GameMap::tileDistance(game_map->worldToTile(getMidPoint()), game_map->worldToTile(player.getMidPoint())) > 8)
  {
    path = AStarPath::resolve(getMidPoint(), player.getMidPoint(), *game_map, *game_data);
    direction = AStarPath::pathPointToDirection(path.front(), getMidPoint());
  }
  else
  {
    fleePathfind(player, dt);
    //shouldn't do it like this, instead use returns to influence behaviour tree.
  }
}

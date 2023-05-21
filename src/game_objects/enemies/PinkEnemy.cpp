//
// Created by Jade on 03/12/2022.
//

#include "PinkEnemy.h"

PinkEnemy::PinkEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map,sf::Vector2f spawn_pos) : Enemy(data, map, spawn_pos)
{
  sprite->setTexture(data->pink_enemy_text);
  default_texture = &data->pink_enemy_text;
}


void PinkEnemy::chasePathfind(Player& player, float& dt)
{
  sf::Vector2i new_target =
    game_map->worldToTile(player.getMidPoint()) +
    sf::Vector2i((int)(3 * player.getDirection().x), (int)(3 * player.getDirection().y));

  if (game_data->floor->getTiles().at(game_map->indexTileByXY(new_target)).ID != 0)
  {
    path = AStarPath::resolve(
      getMidPoint(), game_map->tileToWorld(new_target),
      *game_map,
      *game_data);

    path_target = path.back();
  }
  else
  {
    path = AStarPath::resolve(
      getMidPoint(), player.getMidPoint(), *game_map, *game_data);
  }

  direction = AStarPath::pathPointToDirection(path.front(), getMidPoint());
}

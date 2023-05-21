//
// Created by Jade on 03/12/2022.
//

#include "BlueEnemy.h"

BlueEnemy::BlueEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos) : Enemy(data, map, spawn_pos)
{
  sprite->setTexture(data->blue_enemy_text);
  default_texture = &data->blue_enemy_text;
}

void BlueEnemy::chasePathfind(Player& player, float& dt)
{
  sf::Vector2i new_target_offset = {0, 0};
  sf::Vector2i  new_target_tile;
  new_target_offset.x = (int)((game_map->worldToTile(blinky_ptr->getMidPoint()).x - game_map->worldToTile(pinky_ptr->getTarget()).x));
  new_target_offset.y = (int)((game_map->worldToTile(blinky_ptr->getMidPoint()).y - game_map->worldToTile(pinky_ptr->getTarget()).y));

  new_target_tile = game_map->worldToTile(sf::Vector2f(player.getMidPoint().x + game_map->tileToWorld(new_target_offset).x, player.getMidPoint().y + game_map->tileToWorld(new_target_offset).y));
  if (game_map->indexTileByXY(new_target_tile) < game_data->floor->getTiles().size() && game_data->floor->getTiles().at(game_map->indexTileByXY(new_target_tile)).ID == 73)
  {
    path = AStarPath::resolve(
      getMidPoint(),
      game_map->tileToWorld(new_target_tile),
      *game_map,
      *game_data);
  }
  else
  {
    path = AStarPath::resolve(getMidPoint(), player.getMidPoint(), *game_map, *game_data);
  }

  direction = AStarPath::pathPointToDirection(path.front(), getMidPoint());
}

void BlueEnemy::setBlinkyPinkyRefs(std::shared_ptr<Enemy>* blinky, std::shared_ptr<Enemy>* pinky)
{
  blinky_ptr = *blinky;
  pinky_ptr = *pinky;
}

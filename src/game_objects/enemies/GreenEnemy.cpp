//
// Created by Jade on 03/12/2022.
//

#include "GreenEnemy.h"

GreenEnemy::GreenEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map,sf::Vector2f spawn_pos) : Enemy(data, map, spawn_pos)
{
  sprite->setTexture(data->green_enemy_text);
  default_texture = &data->green_enemy_text;
}

void GreenEnemy::chasePathfind(Player& player, float& dt)
{
  if (path.empty())
  {
    int target_index = rand() % game_data->scatter_points->getObjects().size();
    path = AStarPath::resolve(getMidPoint(), game_map->vect2fConvertTMXtoSFML(game_data->scatter_points->getObjects().at(target_index).getPosition()), *game_map, *game_data);
    direction = AStarPath::pathPointToDirection(path.front(), getMidPoint());
  }
}

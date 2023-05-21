//
// Created by Jade on 21/11/2022.
//

#include "RedEnemy.h"

RedEnemy::RedEnemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos) : Enemy(data, map, spawn_pos)
{
  sprite->setTexture(data->red_enemy_text);
  default_texture = &data->red_enemy_text;
}

void RedEnemy::chasePathfind(Player& player, float& dt)
{
  path = AStarPath::resolve(getMidPoint(), player.getMidPoint(), *game_map, *game_data);
  direction = AStarPath::pathPointToDirection(path.front(), getMidPoint());
}

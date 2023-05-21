//
// Created by Jade on 27/11/2022.
//

#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos) : Entity(data, map, spawn_pos)
{
  speed = 100;
  sprite->setHitBoxCentral(*sprite, 32, 32);
}

void Enemy::die()
{
  caged_duration = 1.0f + rand() % 5;
  spawn();
  is_caged = true;
  caged_timer.restart();
  path.clear();
}


bool Enemy::is_path_empty()
{
  return path.empty();
}

void Enemy::move(float& dt)
{
  if (!path.empty())
  {
    if (abs(GameMap::distance(path.at(0), getMidPoint())) < speed * dt)
    {
      sprite->setHitBoxSpritePos(path.at(0));
      path.erase(path.begin());
      if (!path.empty())
      {
        direction = AStarPath::pathPointToDirection(path.at(0), getMidPoint());
      }
      else
      {
        direction = {0, 0};
      }
      return;
    }

    sprite->moveHitBoxSprite(direction.x * speed * dt, direction.y * speed * dt);
  }
}


void Enemy::fleePathfind(Player& player, float& dt)
{
  int target_index = (int)std::rand() % game_data->scatter_points->getObjects().size();
  sf::Vector2f target = game_map->vect2fConvertTMXtoSFML(game_data->scatter_points->getObjects().at(target_index).getPosition());
  path = AStarPath::resolve(getMidPoint(), target, *game_map, *game_data);
  direction = AStarPath::pathPointToDirection(path.front(), getMidPoint());
}


sf::Vector2f Enemy::getTarget()
{
  return path_target;
}

void Enemy::setFleeingTexture()
{
  sprite->setTexture(game_data->fleeing_texture);
}

void Enemy::setDefaultTexture()
{
  sprite->setTexture(*default_texture);
}

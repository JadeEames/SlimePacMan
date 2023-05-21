//
// Created by Jade on 12/11/2022.
//

#include "Player.h"

Player::Player(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos) :
  Entity(data, map, spawn_pos)
{
  speed = 100;
  sprite->setTexture(game_data->player_text);
  sprite->setHitBoxCentral(*sprite, 32, 32);
  direction_arrow.setTexture(game_data->player_arrow);
  direction_arrow.scale(0.2, 0.2);
  direction_arrow.setOrigin(direction_arrow.getLocalBounds().width/2, direction_arrow.getLocalBounds().height/2);
  lives = max_lives;
}


void Player::update(float& dt)
{
  checkTileCollisions(dt);

  sprite->moveHitBoxSprite((float)current_direction.x * speed * dt,
                           (float)current_direction.y * speed * dt);

  direction_arrow.setPosition(getMidPoint().x + ((float)desired_direction.x * 32), getMidPoint().y + ((float)desired_direction.y * 32));

  if (is_hunting)
  {
    if (hunting_timer.getElapsedTime().asSeconds() > hunting_duration)
    {
      is_hunting = false;
    }
  }
}


void Player::checkTileCollisions(float& dt)
{
  sf::Vector2i current_tile_vec = game_map->worldToTile(getMidPoint());
  sf::Vector2i next_tile_vec = current_tile_vec + current_direction;

  if (desired_direction != current_direction && desired_direction != sf::Vector2i(0, 0))
  {
    sf::Vector2i desired_tile_vec = game_map->worldToTile(getMidPoint()) + desired_direction;
    int desired_tile_id = (int)game_data->floor->getTiles().at(game_map->indexTileByXY(desired_tile_vec)).ID;

    if (desired_tile_id == 73)
    {
      sf::Vector2f next_mid = {getMidPoint().x + (float)current_direction.x * speed * dt, getMidPoint().y + (float)current_direction.y * speed * dt};

      // if next step would take over mid point, set pos to mid point and change direction.
      if (current_direction == sf::Vector2i(0,0))
      {
        current_direction = desired_direction;
      }

      else if (current_direction == sf::Vector2i (0, -1))
      {
        if (next_mid.y < game_map->tileToWorld(desired_tile_vec).y)
        {
          resetPos(current_tile_vec);
          current_direction = desired_direction;
        }
      }

      else if (current_direction == sf::Vector2i (-1, 0))
      {
        if (next_mid.x < game_map->tileToWorld(desired_tile_vec).x)
        {
          resetPos(current_tile_vec);
          current_direction = desired_direction;
        }
      }

      else if (current_direction == sf::Vector2i (0, 1))
      {
        if (next_mid.y > game_map->tileToWorld(desired_tile_vec).y)
        {
          resetPos(current_tile_vec);
          current_direction = desired_direction;
        }
      }

      else if (current_direction == sf::Vector2i (1, 0))
      {
        if (next_mid.x > game_map->tileToWorld(desired_tile_vec).x)
        {
          resetPos(current_tile_vec);
          current_direction = desired_direction;
        }
      }
    }
  }

  // This is gravy: Magic numbers idea (but without magic numbers)
  // Have it before mid point, but only from a certain distance from mid.

  if (game_data->floor->getTiles().at(game_map->indexTileByXY(next_tile_vec)).ID == 0)
  {
    if (Collider::intersects(game_map->getTileBounds(next_tile_vec), sprite->getHitBoxAtNextStep(current_direction, speed, dt)))
    {
      current_direction = {0, 0};
      sprite->setHitBoxSpritePos(game_map->tileToWorld(current_tile_vec));
    }
  }
}


void Player::resetPos(sf::Vector2i& current_tile_vec)
{
  if (!((current_direction.x != 0 && desired_direction.x != 0) || (current_direction.y != 0 && desired_direction.y != 0)))
  {
    sprite->setHitBoxSpritePos(game_map->tileToWorld(current_tile_vec));
  }
}

void Player::spawn()
{
  Entity::spawn();
  current_direction = sf::Vector2i (0, 0);
  desired_direction = sf::Vector2i (0, -1);
  setArrow();
}


void Player::keyPressed(sf::Event event)
{
  switch (event.key.code)
  {
    case sf::Keyboard::W:
    {
      desired_direction = {0,-1};
      setArrow();
      break;
    }

    case sf::Keyboard::A:
    {
      desired_direction = {-1,0};
      setArrow();
      break;
    }

    case sf::Keyboard::S:
    {
      desired_direction = {0,1};
      setArrow();
      break;
    }

    case sf::Keyboard::D:
    {
      desired_direction = {1,0};
      setArrow();
      break;
    }

    default:
    {
      break;
    }
  }
}

void Player::setHuntModeState(bool state)
{
  is_hunting = state;
  hunting_timer.restart();
}


void Player::setArrow()
{
  if (desired_direction.x == 0)
  {
    if (desired_direction.y == 1)
    {
      direction_arrow.setRotation(180);
    }
    else
    {
      direction_arrow.setRotation(0);
    }
  }
  else
  {
    if (desired_direction.x == 1)
    {
      direction_arrow.setRotation(90);
    }
    else
    {
      direction_arrow.setRotation(270);
    }
  }
}

void Player::render()
{
  Entity::render();
  game_data->window->draw(direction_arrow);
}

void Player::die()
{
  spawn();
  lives--;
}


int Player::getLives() const
{
  return lives;
}


sf::Vector2i Player::getDirection()
{
  return current_direction;
}

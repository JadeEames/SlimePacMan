//
// Created by Jade on 12/11/2022.
//

#include "Entity.h"

Entity::Entity(std::shared_ptr<GameData>& data, std::shared_ptr<GameMap>& map, sf::Vector2f spawn_pos)
{
  game_data = data;
  game_map = map;
  sprite = std::make_unique<HitBoxSprite>();
  spawn_point = spawn_pos;
}


void Entity::render()
{
  game_data->window->draw(*sprite);
}


void Entity::setPosition(sf::Vector2f& position)
{
  sf::Vector2i tile = game_map->worldToTile({position.x, position.y});
  sprite->setHitBoxSpritePos(game_map->tileToWorld(tile));
}


void Entity::textureSprite(sf::Texture* texture)
{
  sprite->setTexture(*texture);
}


void Entity::spawn()
{
    setPosition(spawn_point);
}


HitBoxSprite& Entity::getSprite()
{
  return *sprite;
}


sf::Vector2f Entity::getMidPoint()
{
  return { sprite->getGlobalBounds().left + sprite->getGlobalBounds().width / 2,
           sprite->getGlobalBounds().top +
             sprite->getGlobalBounds().height / 2 };
}

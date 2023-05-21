//
// Created by Jade on 18/11/2022.
//

#include "Collectable.h"

sf::Sprite* Collectable::getSprite()
{
  return &sprite;
}


void Collectable::setPositionByMid(sf::Vector2f mid_point)
{
  sprite.setPosition(mid_point.x - sprite.getGlobalBounds().width/2, mid_point.y -sprite.getGlobalBounds().height/2);
}


void Collectable::setTexture(sf::Texture& texture, sf::IntRect& sample_rect)
{
  sprite.setTexture(texture);
  sprite.setTextureRect(sample_rect);
}


void Collectable::setTexture(sf::Texture& texture)
{
  sprite.setTexture(texture);
}


void Collectable::collected(bool state)
{
  picked_up = state;
}


bool& Collectable::collected()
{
  return picked_up;
}


int& Collectable::getPoints()
{
  return points;
}


void Collectable::render(sf::RenderWindow& window)
{
  if (!picked_up)
  {
    window.draw(sprite);
  }
}


void Collectable::setPoints(int input)
{
  points = input;
}

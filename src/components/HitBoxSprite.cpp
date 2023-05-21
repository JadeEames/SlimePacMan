//
// Created by Jade on 12/11/2022.
//

#include "HitBoxSprite.h"


HitBoxSprite::HitBoxSprite()
{
  hit_box = this->getGlobalBounds();
}


void HitBoxSprite::setHitBoxCentral(sf::Sprite& sprite,float width, float height)
{
  float left = sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - width / 2;

  float top = sprite.getPosition().y + (sprite.getGlobalBounds().height / 2) - height / 2;

  hit_box = sf::FloatRect(left, top, width, height);
}

void HitBoxSprite::setHitBox(float x_mid_offset, float y_mid_offset, float width, float height)
{
  hit_box = sf::FloatRect(x_mid_offset, y_mid_offset, width, height);
}


void HitBoxSprite::moveHitBoxSprite(float x, float y)
{
  this->move(x, y);
  hit_box = sf::FloatRect(hit_box.left + x,
                          hit_box.top + y, hit_box.width, hit_box.height);
}


sf::FloatRect& HitBoxSprite::getHitBox()
{
  return hit_box;
}


sf::Vector2f HitBoxSprite::getHitBoxPosition()
{
  return {hit_box.left, hit_box.top};
}


void HitBoxSprite::setHitBoxSpritePos(float mid_x, float mid_y)
{
  this->setPosition(mid_x - this->getGlobalBounds().width / 2, mid_y - this->getGlobalBounds().height / 2);
  hit_box.left = (this->getGlobalBounds().left + this->getGlobalBounds().width / 2) - hit_box.width / 2;
  hit_box.top = (this->getGlobalBounds().top + this->getGlobalBounds().height / 2) - hit_box.height / 2;

}


void HitBoxSprite::setHitBoxSpritePos(sf::Vector2f mid_pos)
{
  this->setPosition(mid_pos.x - this->getGlobalBounds().width / 2, mid_pos.y - this->getGlobalBounds().height / 2);
  hit_box.left = (this->getGlobalBounds().left + this->getGlobalBounds().width / 2) - hit_box.width / 2;
  hit_box.top = (this->getGlobalBounds().top + this->getGlobalBounds().height / 2) - hit_box.height / 2;
}


sf::FloatRect HitBoxSprite::getHitBoxAtNextStep(sf::Vector2i& direction, float& speed, float& dt)
{

  return {hit_box.left + (float)direction.x * speed * dt,
           hit_box.top + (float)direction.y * speed * dt,
           hit_box.width, hit_box.height};
}

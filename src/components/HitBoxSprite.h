//
// Created by Jade on 12/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

class HitBoxSprite : public sf::Sprite
{
 public:
  HitBoxSprite();
  ~HitBoxSprite() override = default;

  void setHitBoxCentral(sf::Sprite& sprite, float width, float height);
  void setHitBox(float x_mid_offset, float y_mid_offset, float width, float height);
  void moveHitBoxSprite(float x, float y);
  void setHitBoxSpritePos(float mid_x, float mid_y);
  void setHitBoxSpritePos(sf::Vector2f mid_pos);
  sf::FloatRect& getHitBox();
  sf::FloatRect getHitBoxAtNextStep(sf::Vector2i& direction, float& speed, float& dt);
  sf::Vector2f getHitBoxPosition();

 private:
  sf::FloatRect hit_box;
};


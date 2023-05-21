//
// Created by Jade on 18/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

enum class MushroomTypes : int
{
  PELLET = 0,
  FRUIT = 1,
  POWER = 2,
  LENGTH = 3
};


class Collectable
{
  public:
  explicit Collectable(MushroomTypes intput_type) : type(intput_type) {};
  ~Collectable() = default;

  const MushroomTypes type;

  sf::Sprite* getSprite();
  void setPositionByMid (sf::Vector2f mid_point);
  void setTexture(sf::Texture& texture);
  void setTexture(sf::Texture& texture, sf::IntRect& sample_rect);
  void collected(bool state);
  bool& collected();
  int& getPoints();
  void setPoints(int input);
  void render(sf::RenderWindow& window);

 private:
  sf::Sprite sprite;
  bool picked_up = false;
  int points     = 0;
};

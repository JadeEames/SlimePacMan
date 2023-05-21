//
// Created by Jade on 09/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

struct Collider
{
 public:
  static bool intersects(sf::FloatRect rect1, sf::FloatRect rect2);
  static bool containsMouse(sf::FloatRect rect1, float x, float y);
  static bool contains(sf::FloatRect contained, sf::FloatRect container);
  static bool windowContains(sf::RenderWindow& window, float x_min, float x_max,float y_min = 1, float y_max = 1);

 private:
  static float max(float a, float b);
  static float min(float a, float b);
};


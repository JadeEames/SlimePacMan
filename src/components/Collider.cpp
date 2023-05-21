//
// Created by Jade on 09/11/2022.
//

#include "Collider.h"

bool Collider::intersects(sf::FloatRect rect1, sf::FloatRect rect2)
{
  float r1_x_min   = rect1.left;
  float r1_x_max   = r1_x_min + rect1.width;
  float r1_y_min   = rect1.top;
  float r1_y_max   = r1_y_min + rect1.height;

  float r2_x_min = rect2.left;
  float r2_x_max = r2_x_min + rect2.width;
  float r2_y_min = rect2.top;
  float r2_y_max = r2_y_min + rect2.height;

  float intersection_x_min = max(r1_x_min, r2_x_min);
  float intersection_x_max = min(r1_x_max, r2_x_max);
  float intersection_y_min = max(r1_y_min, r2_y_min);
  float intersection_y_max = min(r1_y_max, r2_y_max);

  if (intersection_x_min < intersection_x_max && intersection_y_min < intersection_y_max)
  {
    return true;
  }

  return false;
}

bool Collider::containsMouse(sf::FloatRect rect1, float x, float y)
{
  if (rect1.left < x && x < rect1.left + rect1.width
      && rect1.top < y && y < rect1.top + rect1.height)
  {
    return true;
  }

  return false;
}

bool Collider::contains(sf::FloatRect contained, sf::FloatRect container)
{
  if (contained.left + contained.width < container.left + container.width &&
      contained.left > container.left && contained.top > container.top &&
      contained.top + contained.height < container.top + container.height)
  {
    return true;
  }

  return false;
}

bool Collider::windowContains(sf::RenderWindow& window, float x_min, float x_max,
                              float y_min, float y_max)
{
  if (x_min > 0 && x_max < float(window.getSize().x) && y_min > 0 &&
      y_max < float(window.getSize().y))
  {
    return true;
  }

  return false;
}

float Collider::max(float a, float b)
{
  if (a > b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

float Collider::min(float a, float b)
{
  if (a < b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

//
// Created by Jade on 09/11/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>


class Helper
{
 public:
  static void textInit(sf::Text& text, std::string string, sf::Font& font,
                       sf::Color fill_colour, int char_size = 50,
                       float x_pos = 100, float y_pos = 100);

  static void textSetPosInWindow(sf::Text& text, sf::RenderWindow& window,
                                 float x_mid_offset = 0, float y_mid_offset = 0);

  static std::string padStringLeft(std::string string, char padding_char, int padding_num);
};

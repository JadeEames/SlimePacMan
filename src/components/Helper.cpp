//
// Created by Jade on 09/11/2022.
//

#include "Helper.h"


void Helper::textInit(sf::Text& text, std::string string, sf::Font& font,
                      sf::Color fill_colour, int char_size,
                      float x_pos, float y_pos)
{
  text.setString(string);
  text.setFont(font);
  text.setFillColor(fill_colour);
  text.setCharacterSize(char_size);
  text.setPosition(x_pos, y_pos);
}


void Helper::textSetPosInWindow(sf::Text& text, sf::RenderWindow& window,
                                float x_mid_offset, float y_mid_offset)
{
  float x_pos = float(window.getSize().x) / 2 -
                text.getGlobalBounds().width / 2 + x_mid_offset;

  float y_pos = float(window.getSize().y) / 2 -
                text.getGlobalBounds().height / 2 + y_mid_offset;

  text.setPosition(x_pos, y_pos);
}


std::string Helper::padStringLeft(std::string string, char padding_char, int padding_num)
{
  // https://stackoverflow.com/questions/667183/padding-stl-strings-in-c

  if (string.size() < padding_num)
  {
    std::string padded(padding_num - string.size(), padding_char);
    padded += string;
    return padded;
  }
  return string;
}

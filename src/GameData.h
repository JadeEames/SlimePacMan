//
// Created by Jade on 26/10/2022.
//

#pragma once

// Libraries
#include <SFML/Graphics.hpp>

// This codebase
#include "states/StateEnum.h"
#include "tmxlite/TileLayer.hpp"
#include "map/MapFiles.h"

struct GameData
{
 public:
  std::unique_ptr<sf::RenderWindow> window = nullptr;
  std::vector<MapFiles> map_filepaths;
  int selected_map = 0;

  tmx::TileLayer* floor = nullptr;
  tmx::ObjectGroup* player_spawn = nullptr;
  tmx::ObjectGroup* ghost_spawns = nullptr;
  tmx::ObjectGroup* scatter_points = nullptr;

  sf::View normal_view;
  sf::View map_view;

  sf::Font font;
  sf::Color orange = sf::Color(  245, 167, 64);
  sf::Color grey = sf::Color(169,169,169);
  sf::Color background_brown = sf::Color(48, 44, 46);

  StateEnum current_state = StateEnum(0);
  bool prep_next_state    = false;
  int score = 0;

  sf::Texture fleeing_texture;
  sf::Texture player_text;
  sf::Texture red_enemy_text;
  sf::Texture pink_enemy_text;
  sf::Texture orange_enemy_text;
  sf::Texture blue_enemy_text;
  sf::Texture green_enemy_text;
  sf::Texture player_arrow;
  sf::Texture mushrooms_text;
  std::vector<sf::IntRect> mushroom_sample_rects;
};


//
// Created by Jade on 26/10/2022.
//

#pragma once

// Libraries
#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <cmath>

// This codebase
#include "../GameData.h"
#include "VertexArrayMap.h"
#include "MapFiles.h"

class GameMap
{
 public:
  GameMap() = default;
  ~GameMap() = default;

  bool loadMap(GameData& data, const MapFiles& map_files);
  bool imageFileCheck(const std::string& file_path);
  void renderMap(sf::RenderWindow&);

  sf::Vector2i worldToTile(sf::Vector2f world);
  sf::Vector2f tileToWorld(sf::Vector2i tile);
  sf::FloatRect getTileBounds(sf::Vector2i& tile_vec);
  int indexTileByXY(sf::Vector2i tile_vect);
  sf::Vector2i indexToTileVec(int index);
  static sf::Vector2f vect2fConvertTMXtoSFML(const tmx::Vector2<float>& tmx_vect);
  static float distance(sf::Vector2f a, sf::Vector2f b);
  static int tileDistance(sf::Vector2i a, sf::Vector2i b);

  std::vector<std::shared_ptr<VertexArrayMap>> renderable_layers;
  std::shared_ptr<tmx::Map> tmx_map = nullptr;

  sf::Sprite map_sprite;
  sf::Texture map_texture;

  int total_layers = 0;

 private:
  void createVertexArrayObjects(const std::string& tilesheet);
  void createTexture(GameData& data);
  void saveImage(const std::string& image_path);
};

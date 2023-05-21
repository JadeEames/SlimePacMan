//
// Created by Jade on 01/11/2022.
//

#pragma once

// Libraries
#include <tmxlite/Types.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>



class VertexArrayMap : public sf::Drawable, public sf::Transformable
{
 public:
  VertexArrayMap() = default;
  ~VertexArrayMap() override = default;

  bool load(const std::string& tileset_path,
            const tmx::Vector2u& tile_size,
            const tmx::Vector2u& map_size,
            const std::vector<tmx::TileLayer::Tile>& tiles);

 private:
  sf::Texture tileset_text;
  sf::VertexArray vertices;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
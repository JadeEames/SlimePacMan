//
// Created by Jade on 01/11/2022.
//

#include "VertexArrayMap.h"

bool VertexArrayMap::load(const std::string& tileset_path, const tmx::Vector2u& tile_size, const tmx::Vector2u& map_size, const std::vector<tmx::TileLayer::Tile>& tiles)
{
  if (!tileset_text.loadFromFile(tileset_path))
  {
    return false;
  }

  vertices.setPrimitiveType(sf::Quads);
  vertices.resize( map_size.x * map_size.y * 4);

  for (unsigned int i = 0; i < map_size.x; i++)
  {
    for (unsigned int j = 0; j < map_size.y; j++)
    {
      int tile_number = (int)(tiles.at(i + j * map_size.x).ID);

      if (tile_number == 0) // Skip tiles with the ID 0 as they are blank/transparent.
      {
        continue;
      }

      tile_number--; // Increment tile ID number because between Tiled and Clion IDs have been shifted along by one.
      int texture_u = tile_number % (tileset_text.getSize().x / tile_size.x);
      int texture_v = tile_number / (tileset_text.getSize().x / tile_size.x);


      sf::Vertex* quad = &vertices[(i + j * map_size.x) * 4];

      quad[0].position = sf::Vector2f(i * tile_size.x, j * tile_size.y);
      quad[1].position = sf::Vector2f((i + 1) * tile_size.x, j * tile_size.y);
      quad[2].position = sf::Vector2f((i + 1) * tile_size.x, (j + 1) * tile_size.y);
      quad[3].position = sf::Vector2f(i * tile_size.x, (j + 1) * tile_size.y);

      quad[0].texCoords = sf::Vector2f(texture_u * tile_size.x, texture_v * tile_size.y);
      quad[1].texCoords = sf::Vector2f((texture_u + 1) * tile_size.x, texture_v * tile_size.y);
      quad[2].texCoords = sf::Vector2f((texture_u + 1) * tile_size.x, (texture_v + 1) * tile_size.y);
      quad[3].texCoords = sf::Vector2f(texture_u * tile_size.x, (texture_v + 1) * tile_size.y);


//      Didn't like making every tile a sprite so instead wanted something else.
//      Found this tutorial for making a vertex array with quads representing each tile.
//      https://www.sfml-dev.org/tutorials/2.5/graphics-vertex-array.php#example-tile-map


    }
  }

  return true;
}


void VertexArrayMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  states.texture = &tileset_text;

  target.draw(vertices, states);
}

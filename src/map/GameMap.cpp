//
// Created by Jade on 26/10/2022.
//

#include "GameMap.h"


bool GameMap::loadMap(GameData& data, const MapFiles& map_files)
{
  tmx_map = std::make_shared<tmx::Map>();

  if (!tmx_map->load(map_files.tmx_path))
  {
    std::cout << "Failed to load tilemap tmx" << std::endl;
    return false;
  }


  total_layers = (int)(tmx_map->getLayers().size());
  for (unsigned int layer_num = 0; layer_num < total_layers; layer_num++)
  {
    if (tmx_map->getLayers()[layer_num]->getType() == tmx::Layer::Type::Tile)
    {
      if (tmx_map->getLayers()[layer_num]->getName() == "walkable")
      {
        data.floor = &tmx_map->getLayers()[layer_num]->getLayerAs<tmx::TileLayer>();
      }
    }
    else if (tmx_map->getLayers()[layer_num]->getType() == tmx::Layer::Type::Object)
    {
      if (tmx_map->getLayers()[layer_num]->getName() == "player_spawn")
      {
        data.player_spawn = &tmx_map->getLayers()[layer_num]->getLayerAs<tmx::ObjectGroup>();
      }
      else if (tmx_map->getLayers()[layer_num]->getName() == "ghosts")
      {
        data.ghost_spawns = &tmx_map->getLayers()[layer_num]->getLayerAs<tmx::ObjectGroup>();
      }
      else if (tmx_map->getLayers()[layer_num]->getName() == "scatter_points")
      {
        data.scatter_points = &tmx_map->getLayers()[layer_num]->getLayerAs<tmx::ObjectGroup>();
      }
    }
  }

  if (!imageFileCheck(map_files.map_texture_path))
  {
//    If map_image doesn't exist, creates an image, loads it to map_texture and saves the image.
//    BUT does not use it.
//    Don't make use of the png created until the second run
//    as it feels silly to be taking an sf::texture (result of createTexture()), converting it to an sf::image
//    and saving this image to the disk only to then pull it back in and load it to a texture.
//    https://en.sfml-dev.org/forums/index.php?topic=13799.0

    createVertexArrayObjects(map_files.tilesheet_path);
    createTexture( data);
    saveImage(map_files.map_texture_path);
  }

  map_sprite.setTexture(map_texture);
  return true;
}


void GameMap::createVertexArrayObjects(const std::string& tilesheet)
{
  for (unsigned int layer_num = 0; layer_num < total_layers; layer_num++)
  {
    if (tmx_map->getLayers()[layer_num]->getType() != tmx::TileLayer::Type::Tile)
    {
      continue;
    }
    else
    {
      renderable_layers.emplace_back(std::make_shared<VertexArrayMap>());
      renderable_layers[layer_num]->load(
        tilesheet,
        tmx_map->getTileSize(),
        tmx_map->getTileCount(),
        tmx_map->getLayers()[layer_num]
          ->getLayerAs<tmx::TileLayer>()
          .getTiles());
    }
  }
}


void GameMap::createTexture(GameData& data)
{
//  https://www.sfml-dev.org/tutorials/2.5/graphics-draw.php#off-screen-drawing
  sf::RenderTexture render_texture;
  render_texture.create(tmx_map->getTileSize().x * tmx_map->getTileCount().x,
                        tmx_map->getTileSize().y * tmx_map->getTileCount().y);
  render_texture.clear(data.background_brown);

  for (auto & renderable_layer : renderable_layers)
  {
    render_texture.draw(*renderable_layer);
  }

  render_texture.display();
  map_texture = render_texture.getTexture();
}


void GameMap::saveImage(const std::string& image_path)
{
  sf::Image image;
  image = map_texture.copyToImage();
  image.saveToFile(image_path);
}


bool GameMap::imageFileCheck(const std::string& file_path)
{
  if (!map_texture.loadFromFile(file_path))
  {
    return false;
  }

  return true;
}


void GameMap::renderMap(sf::RenderWindow& window)
{
  window.draw(map_sprite);
}


sf::Vector2i GameMap::worldToTile(sf::Vector2f world)
{
  return {(int)(world.x / (float)tmx_map->getTileSize().x), (int)(world.y / (float)tmx_map->getTileSize().y)};
}


sf::Vector2f GameMap::tileToWorld(sf::Vector2i tile)
{
  //returns tile mid point.
  return {(float)(tile.x + 1) * (float)tmx_map->getTileSize().x - (float)(tmx_map->getTileSize().x * 0.5),
           (float)(tile.y + 1) * (float)tmx_map->getTileSize().y - (float)(tmx_map->getTileSize().y * 0.5)};
}


int GameMap::indexTileByXY(sf::Vector2i tile_vec)
{
  return tile_vec.y * tmx_map->getTileCount().x + tile_vec.x;
}


sf::Vector2i GameMap::indexToTileVec(int index)
{
  int x = index % (int)tmx_map->getTileCount().x;
  int y = (index - x) / (int)tmx_map->getTileCount().y;
  return {x, y};
}


sf::FloatRect GameMap::getTileBounds(sf::Vector2i& tile_vec)
{
  sf::FloatRect bounds;
  bounds.width = (float)tmx_map->getTileSize().x;
  bounds.height = (float)tmx_map->getTileSize().y;

  bounds.left = (float)tile_vec.x * (float)tmx_map->getTileSize().x;
  bounds.top = (float)tile_vec.y * (float)tmx_map->getTileSize().y;

  return bounds;
}


sf::Vector2f GameMap::vect2fConvertTMXtoSFML(const tmx::Vector2<float>& tmx_vect)
{
  return {tmx_vect.x, tmx_vect.y};
}


float GameMap::distance(sf::Vector2f a, sf::Vector2f b)
{
  return abs(a.x - b.x) + abs(a.y - b.y);
}

int GameMap::tileDistance(sf::Vector2i a, sf::Vector2i b)
{
  return abs(a.x - b.x) + abs(a.y - b.y);
}

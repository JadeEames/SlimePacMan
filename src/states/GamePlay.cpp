//
// Created by Jade on 10/11/2022.
//

#include "GamePlay.h"


GamePlay::GamePlay(std::shared_ptr<GameData> data) : State(data) {}


void GamePlay::initState()
{
  life_hearts_texture.loadFromFile("Data/Images/LifeHearts.png");
  life_hearts.setTexture(life_hearts_texture);
  heart_width = int(life_hearts_texture.getSize().x) / 3;
  life_hearts.setPosition(-10, 100);

  Helper::textInit(score_text, Helper::padStringLeft(std::to_string(game_data->score), '0', 8), game_data->font, game_data->orange, 40);
  score_text.setPosition(820, 80);
}


void GamePlay::update(float& dt)
{
  player->update(dt);
  checkCurrentTileCollectableCollision();
  director->tick(*player, dt);
  playerEnemyCollisions();

  if (available_pickups == 0)
  {
    game_data->current_state = StateEnum::WIN_MENU;
    game_data->prep_next_state = true;
  }
  else if (player->getLives() < 1)
  {
    game_data->current_state = StateEnum::LOSE_MENU;
    game_data->prep_next_state = true;
  }
}


void GamePlay::render()
{
  game_data->window->setView(game_data->map_view);
  game_data->window->draw(background);
  map->renderMap(*game_data->window);
  game_data->window->draw(score_text);

  for (auto pickup : pickups)
  {
    pickup.second.render(*game_data->window);
  }

  for (auto& enemy : enemies)
  {
    enemy->render();
  }
  player->render();
  game_data->window->draw(life_hearts);
}


void GamePlay::keyPressed(sf::Event event)
{
  player->keyPressed(event);
  if (event.key.code == sf::Keyboard::Period)
  {
    available_pickups = 0;
  }
}


void GamePlay::prepState()
{
  pickups.clear();
  game_data->score = 0;
  updateScoreText();
  enemies.clear();
  loadMapAndDependentStuff();
  for (auto& enemy : enemies)
  {
    enemy->die();
  }
  updateUIHearts();
}


void GamePlay::checkCurrentTileCollectableCollision()
{
  //  Collectable& nearest_collectable = pickups.at(map->indexTileByXY(map->worldToTile(player->getMidPoint())));
  //
  //  if (!nearest_collectable.collected())
  //  {
  //    if (Collider::contains(nearest_collectable.getSprite()->getGlobalBounds(),
  //                           player->getSprite().getHitBox()))
  //    {
  //      game_data->points += nearest_collectable.getPoints();
  //      nearest_collectable.collected(true);
  //    }
  //  }

  // ^^^^^^^^ Thought I could use the above code, but realised that I don't add collectables for tiles with an ID of 0.
  // Therefor, the order of the vector does not match the grid.
  // I could change it to create a collectable for all tiles, while it would be nice
  // because I would only have to check one collectable per update, I don't want to waste the memory.
  // I could use a quad tree, but should finish the game first.
  // OR an unordered map with first being a sf::Vector2i (tilexy) and second being the collectable?

  //  for (int i = 0; i < pickups.size() - 1; i++)
  //  {
  //    Collectable& pickup = pickups.at(i);
  //    if (!pickup.collected())
  //    {
  //      if (Collider::contains(pickup.getSprite()->getGlobalBounds(), player->getSprite().getHitBox()))
  //      {
  //        game_data->score += pickup.getPoints();
  //        pickup.collected(true);
  //      }
  //    }
  //  }

  int current_player_tile = map->indexTileByXY(map->worldToTile(player->getMidPoint()));

  if (pickups.find(current_player_tile) == pickups.end())
  {
    return;
  }

  Collectable& pickup = pickups.at(current_player_tile);
  if (!pickup.collected())
  {
    if (Collider::contains(pickup.getSprite()->getGlobalBounds(), player->getSprite().getHitBox()))
    {
      game_data->score += pickup.getPoints();
      pickup.collected(true);
      updateScoreText();
      available_pickups -= 1;

      if (pickup.type == MushroomTypes::POWER)
      {
        player->setHuntModeState(true);
      }
    }
  }

  //nvm did it before finishing the game because I realised how easy it would be to set this up.
}


void GamePlay::updateScoreText()
{
  score_text.setString(Helper::padStringLeft(std::to_string(game_data->score), '0', 8));
}


void GamePlay::playerEnemyCollisions()
{
  bool restart = false;
  for (auto& enemy : enemies)
  {
    if (Collider::intersects(player->getSprite().getHitBox(), enemy->getSprite().getHitBox()))
    {
      if (player->is_hunting)
      {
        enemy->die();
      }
      else
      {
        restart = true;
        player->die();
        updateUIHearts();
      }
    }
  }

  if (restart)
  {
    for (auto& enemy : enemies)
    {
      enemy->die();
    }
  }
}

void GamePlay::updateUIHearts()
{
  life_hearts.setTextureRect({ 0,
                               0,
                               player->getLives() * heart_width,
                               int(life_hearts_texture.getSize().y) });
}

void GamePlay::loadMapAndDependentStuff()
{
  map = std::make_shared<GameMap>();
  map->loadMap(*game_data, game_data->map_filepaths[game_data->selected_map]);

  game_data->map_view.setSize(
    float(game_data->window->getSize().x),
    float(game_data->window->getSize().y));
  game_data->map_view.setCenter(
    map->map_sprite.getGlobalBounds().left +
      map->map_sprite.getGlobalBounds().width / 2,
    map->map_sprite.getGlobalBounds().top +
      map->map_sprite.getGlobalBounds().height / 2);


  int count = -1;

  sf::Vector2i player_spawn_tile =  map->worldToTile(map->vect2fConvertTMXtoSFML(game_data->player_spawn->getObjects().front().getPosition()));
  for (tmx::TileLayer::Tile tile : game_data->floor->getTiles())
  {
    count++;

    if (tile.ID == 73)
    {
      if (map->indexToTileVec(count) == player_spawn_tile)
      {
        continue;
      }


      available_pickups += 1;
      auto type = (float)rand() / RAND_MAX;

      if (type < 0.018) // Power mushroom.
      {
        pickups.insert(std::make_pair(count, Collectable(MushroomTypes::POWER)));
        pickups.at(count).setTexture(
          game_data->mushrooms_text,
          game_data->mushroom_sample_rects.at((int)MushroomTypes::POWER));
        pickups.at(count).setPoints(20);
      }
      else if (type < 0.10) // Fruit mushroom.
      {
        pickups.insert(std::make_pair(count, Collectable(MushroomTypes::FRUIT)));
        pickups.at(count).setTexture(
          game_data->mushrooms_text,
          game_data->mushroom_sample_rects.at((int)MushroomTypes::FRUIT));
        pickups.at(count).setPoints(10);
      }
      else // Pellet mushroom.
      {
        pickups.insert(std::make_pair(count, Collectable(MushroomTypes::PELLET)));
        pickups.at(count).setTexture(
          game_data->mushrooms_text,
          game_data->mushroom_sample_rects.at((int)MushroomTypes::PELLET));
        pickups.at(count).setPoints(5);
      }
      pickups.at(count).setPositionByMid(map->tileToWorld(map->indexToTileVec(count)));
    }
  }

  player = std::make_shared<Player>(game_data, map, map->vect2fConvertTMXtoSFML(game_data->player_spawn->getObjects().front().getPosition()));
  player->spawn();


  enemies.emplace_back(std::make_shared<RedEnemy>(game_data,map, map->vect2fConvertTMXtoSFML(game_data->ghost_spawns->getObjects().at(0).getPosition())));
  enemies.emplace_back(std::make_shared<PinkEnemy>(game_data,map, map->vect2fConvertTMXtoSFML(game_data->ghost_spawns->getObjects().at(1).getPosition())));
  enemies.emplace_back(std::make_shared<OrangeEnemy>(game_data,map, map->vect2fConvertTMXtoSFML(game_data->ghost_spawns->getObjects().at(2).getPosition())));
  enemies.emplace_back(std::make_shared<BlueEnemy>(game_data,map, map->vect2fConvertTMXtoSFML(game_data->ghost_spawns->getObjects().at(2).getPosition())));
  dynamic_cast<BlueEnemy&>(*enemies.back()).setBlinkyPinkyRefs(&enemies.at(0), &enemies.at(1));
  enemies.emplace_back(std::make_shared<GreenEnemy>(game_data,map, map->vect2fConvertTMXtoSFML(game_data->ghost_spawns->getObjects().at(2).getPosition())));
  for (auto& enemy : enemies)
  {
    enemy->spawn();
  }

  director = std::make_unique<BehaviourTree>(&enemies);
}

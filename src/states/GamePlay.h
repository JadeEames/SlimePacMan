//
// Created by Jade on 10/11/2022.
//

#pragma once

// This codebase
#include "../states/State.h"
#include "../map/GameMap.h"
#include "../game_objects/Player.h"
#include "../game_objects/enemies/RedEnemy.h"
#include "../game_objects/enemies/PinkEnemy.h"
#include "../game_objects/enemies/OrangeEnemy.h"
#include "../game_objects/enemies/BlueEnemy.h"
#include "../game_objects/enemies/GreenEnemy.h"
#include "../game_objects/Collectable.h"
#include "../components/behaviour_tree/BehaviourTree.h"

class GamePlay : public State
{
 public:
  explicit GamePlay(std::shared_ptr<GameData> data);
  ~GamePlay() = default;

  void initState() override;
  void update(float& dt) override;
  void render() override;
  void keyPressed(sf::Event event) override;
  void prepState() override;


 private:
  std::shared_ptr<GameMap> map; 
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::unordered_map<int, Collectable> pickups;
  std::unique_ptr<BehaviourTree> director;

  sf::Text score_text;
  int available_pickups = 0;

  sf::Sprite life_hearts;
  sf::Texture life_hearts_texture;
  int heart_width = 0.0f;

  void loadMapAndDependentStuff();
  void checkCurrentTileCollectableCollision();
  void updateScoreText();
  void playerEnemyCollisions();
  void updateUIHearts();
};

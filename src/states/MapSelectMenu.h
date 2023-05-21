//
// Created by Jade on 02/12/2022.
//

#pragma once

// This codebase
#include "State.h"
#include "../components/Helper.h"
#include "../components/Collider.h"

enum class MapOptions : int
{
  ORIGINAL   = 0,
  OTHER      = 1,
  ENUMLENGTH = 2
};

class MapSelectMenu : public State
{
 public:
  explicit MapSelectMenu(std::shared_ptr<GameData> data);
  ~MapSelectMenu() = default;

  void initState() override;
  void render() override;

  void mouseClicked(sf::Event event) override;
  void mouseMoved(sf::Event event) override;
  void keyPressed(sf::Event event) override;
  void prepState() override {};

 private:
  sf::Texture background_text2;

  MapOptions selected_option;
  sf::Text title_text;
  std::vector<sf::Text> option_texts;

  void swapSelectionColours();
};

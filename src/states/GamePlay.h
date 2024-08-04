#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Component.hpp"
#include "Constants.hpp"
#include "Game.h"
#include "Scene.hpp"
#include "State.h"
#include "System.hpp"

class GamePlay : public State {
 public:
  GamePlay(std::shared_ptr<Context> context);
  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;

  void componentSelection();

 private:
  std::shared_ptr<Context> context;
  std::shared_ptr<Scene> scene;
  System system;

  sf::Vector2i moveDir;
  EntityID player;

  sf::Clock deltaClock;
};
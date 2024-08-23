#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Component.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "ImGuiHelper.hpp"
#include "SaveManager.hpp"
#include "Scene.hpp"
#include "State.hpp"
#include "system/System.hpp"
#include "system/UiSystem.hpp"
#include "ImageLoader.hpp"

class GamePlay : public State {
 public:
  GamePlay(std::shared_ptr<Context> context);
  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;
  void handleSaveButton();

 private:
  std::shared_ptr<Context> context;
  std::shared_ptr<Scene> scene;
  System system;
  UiSystem uiSystem;

  sf::Vector2i moveDir;
  EntityID player;

  sf::Clock deltaClock;
  void drawDebugLines();
};
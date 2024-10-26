#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "CombatLog.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include "ImGuiHelper.hpp"
#include "ImageLoader.hpp"
#include "ImageNames.hpp"
#include "Scene.hpp"
#include "State.hpp"
#include "component/ActorComponent.hpp"
#include "component/Component.hpp"
#include "component/ItemComponent.hpp"
#include "system/BehaviorSystem.hpp"
#include "system/EnemySystem.hpp"
#include "system/System.hpp"
#include "system/UiSystem.hpp"
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
  EnemySystem enemySystem;

  sf::Vector2i moveDir;
  EntityID player;

  Inventory inventory;
  EquippedItems equippedItems;
  void mockCreateInventory();

  sf::Clock deltaClock;
  void drawDebugLines();

  void loadPlayer(json &save);
  void updateSave();
  BT::Tree tree;
};
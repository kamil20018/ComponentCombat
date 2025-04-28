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
#include "Timer.hpp"
#include "component/ActorComponent.hpp"
#include "component/Component.hpp"
#include "component/EntityComponent.hpp"
#include "system/BehaviorSystem.hpp"
#include "system/EffectSystem.hpp"
#include "system/EnemySystem.hpp"
#include "system/System.hpp"
#include "system/TraitActivator.hpp"
#include "system/UiSystem.hpp"

class GamePlay : public State {
 public:
  GamePlay(std::shared_ptr<Context> context, bool newGame = false);
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
  TraitActivator traitActivator;
  std::shared_ptr<EffectSystem> effectSystem;

  bool newGame;

  sf::Vector2i moveDir;
  bool playerUsedAction;
  EntityID player;
  bool passTurn = false;

  bool inventoryOpen = false;
  bool logOpened = false;

  Inventory inventory;
  EquippedItems equippedItems;
  void mockCreateInventory();

  sf::Clock deltaClock;
  sf::Vector2i getMouseTilePosition();
  void drawDebugLines();

  json savePlayer();
  void loadPlayer(json &save);
  json saveMetaProgression();
  json saveStateDestination();
  void updateSave();
};
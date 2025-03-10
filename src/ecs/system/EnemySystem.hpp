#pragma once

#include <sstream>

#include "CombatLog.hpp"
#include "Context.hpp"
#include "Scene.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include "component/ActorComponent.hpp"
#include "component/ComponentHelpers.hpp"
#include "component/TraitComponent.hpp"
#include "system/BehaviorSystem.hpp"
#include "system/EffectSystem.hpp"
using ss = std::stringstream;
class EnemySystem {
 public:
  EnemySystem();
  EnemySystem(std::shared_ptr<Scene> scene, std::shared_ptr<EffectSystem> effectSystem, std::shared_ptr<Context> context);
  EntityID spawn(int variant);
  void enemyTurn();
  void setPlayer(EntityID player);

  json saveEnemies();
  void loadEnemies(json &j);
  void loadEnemyRequired(const json &enemySave, EntityID enemyID);
  void loadEnemyBT(const json &enemySave, EntityID enemyID);
  void loadEnemyOptional(const json &enemySave, EntityID enemyID);

 private:
  BT::BehaviorTreeFactory BTmelee(EntityID entityID);
  BT::BehaviorTreeFactory BTranger(EntityID entityID);
  std::vector<EntityID> enemies;
  std::shared_ptr<Scene> scene;
  std::shared_ptr<EffectSystem> effectSystem;
  std::shared_ptr<Context> context;
  EntityID player;
};

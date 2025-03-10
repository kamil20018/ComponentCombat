#include "EnemySystem.hpp"

EnemySystem::EnemySystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

EntityID EnemySystem::spawn(int variant) {
  auto enemy = scene->createEntity();
  enemies.push_back(enemy);

  if (variant == 0) {
    scene->addComponents(
        enemy, std::make_shared<BodyColor>(sf::Color::Blue), std::make_shared<Position>(sf::Vector2i(0, 10)), std::make_shared<Name>((std::string) "Blue"),
        std::make_shared<Size>(40, 40), std::make_shared<Sight>(4), std::make_shared<Hp>(7),
        std::make_shared<BehaviorTree>(BTmelee(enemy), fs::current_path().parent_path() / "resources" / "behavior_trees" / "melee.xml", BtType::MELEE),
        std::make_shared<MeleeAttack>(2));
  }
  return enemy;
}

void EnemySystem::setPlayer(EntityID player) {
  this->player = player;
}

void EnemySystem::enemyTurn(EffectSystem &effectSystem) {
  for (const auto &enemy : enemies) {
    scene->getComponent<BehaviorTree>(enemy)->tree.tickOnce();
    effectSystem.updateEffectStatuses();
  }
}

json EnemySystem::saveEnemies() {
  json save;
  for (const auto &enemy : enemies) {
    save.push_back(scene->getEntitySave(enemy));
  }
  return {"enemies", save};
}

void EnemySystem::loadEnemies(json &j) {
  for (const auto &enemySave : j) {
    EntityID enemyID = scene->createEntity();
    enemies.push_back(enemyID);
    loadEnemyRequired(enemySave, enemyID);
    loadEnemyOptional(enemySave, enemyID);
  }
}

void EnemySystem::loadEnemyRequired(const json &enemySave, EntityID enemyID) {
  scene->addComponents(enemyID, std::make_shared<BodyColor>(enemySave), std::make_shared<Position>(enemySave), std::make_shared<Hp>(enemySave),
                       std::make_shared<Name>(enemySave), std::make_shared<Size>(enemySave), std::make_shared<Sight>(enemySave));
  loadEnemyBT(enemySave, enemyID);
}

void EnemySystem::loadEnemyBT(const json &enemySave, EntityID enemyID) {
  switch (StringToBtType.at(enemySave["behaviorTree"]["type"])) {
    case BtType::MELEE:
      scene->addComponent(enemyID, std::make_shared<BehaviorTree>(BTmelee(enemyID), enemySave));
      scene->addComponent(enemyID, std::make_shared<MeleeAttack>(enemySave));
      break;
    case BtType::RANGED:
      scene->addComponents(enemyID, std::make_shared<BehaviorTree>(BTranger(enemyID), enemySave), std::make_shared<RangedAttack>(enemySave));
      break;
  }
}

void EnemySystem::loadEnemyOptional(const json &enemySave, EntityID enemyID) {}

BT::BehaviorTreeFactory EnemySystem::BTranger(EntityID enemyID) {
  BT::BehaviorTreeFactory rangerBT;
  rangerBT.registerNodeType<InSight>("InSight", player, enemyID, scene);
  rangerBT.registerNodeType<InRangeGeneric<RangedAttack>>("InRangeGeneric", player, enemyID, scene);
  rangerBT.registerNodeType<PerformRangedAttack>("PerformRangedAttack", player, enemyID, scene);
  rangerBT.registerNodeType<ApproachPlayer>("ApproachPlayer", player, enemyID, scene);
  return std::move(rangerBT);
}

BT::BehaviorTreeFactory EnemySystem::BTmelee(EntityID enemyID) {
  BT::BehaviorTreeFactory meleeBT;
  meleeBT.registerNodeType<InSight>("InSight", player, enemyID, scene);
  meleeBT.registerNodeType<IsNextToPlayer>("IsNextToPlayer", player, enemyID, scene);
  meleeBT.registerNodeType<PerformMeleeAttack>("PerformMeleeAttack", player, enemyID, scene);
  meleeBT.registerNodeType<ApproachPlayer>("ApproachPlayer", player, enemyID, scene);
  meleeBT.registerNodeType<Wander>("Wander", enemyID, scene);
  return std::move(meleeBT);
}
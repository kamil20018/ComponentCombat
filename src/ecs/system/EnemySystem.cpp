#include "EnemySystem.hpp"

EnemySystem::EnemySystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

EntityID EnemySystem::spawn(int variant) {
  auto enemy = scene->createEntity();
  enemies.push_back(enemy);

  if (variant == 0) {
    scene->addComponents(
        enemy, std::make_shared<BodyColor>(sf::Color::Red), std::make_shared<Position>(sf::Vector2i(0, 10)), std::make_shared<Name>((std::string) "Fag"),
        std::make_shared<Size>(40, 40), std::make_shared<Sight>(14), std::make_shared<RangedAttack>(8, 10), std::make_shared<Hp>(7),
        std::make_shared<BehaviorTree>(BTranger(enemy), fs::current_path().parent_path() / "resources" / "behavior_trees" / "ranger.xml", BtType::LONG_RANGE));
  }
  return enemy;
}

void EnemySystem::setPlayer(EntityID player) {
  this->player = player;
}

void EnemySystem::enemyTurn() {
  for (const auto &enemy : enemies) {
    scene->getComponent<BehaviorTree>(enemy)->tree.tickOnce();
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
    scene->addComponents(enemyID, std::make_shared<BodyColor>(enemySave), std::make_shared<Position>(enemySave), std::make_shared<Hp>(enemySave),
                         std::make_shared<Name>(enemySave), std::make_shared<Size>(enemySave), std::make_shared<Sight>(enemySave),
                         std::make_shared<BehaviorTree>(BTranger(enemyID), enemySave), std::make_shared<RangedAttack>(enemySave));
  }
}

BT::BehaviorTreeFactory EnemySystem::BTranger(EntityID entityID) {
  BT::BehaviorTreeFactory rangerBT;
  rangerBT.registerNodeType<InSight>("InSight", player, entityID, scene);
  rangerBT.registerNodeType<InRangeGeneric<RangedAttack>>("InRangeGeneric", player, entityID, scene);
  rangerBT.registerNodeType<PerformRangedAttack>("PerformRangedAttack", player, entityID, scene);
  rangerBT.registerNodeType<ApproachPlayer>("ApproachPlayer", player, entityID, scene);
  return std::move(rangerBT);
}
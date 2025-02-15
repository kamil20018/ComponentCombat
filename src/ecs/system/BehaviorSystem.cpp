#include "BehaviorSystem.hpp"
InSight::InSight(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
    : BT::ConditionNode(name, config), player(player), enemy(enemy), scene(scene) {}

BT::PortsList InSight::providedPorts() {
  return {};
}

BT::NodeStatus InSight::tick() {
  auto playerPos = scene->getComponent<Position>(player);
  auto enemyPos = scene->getComponent<Position>(enemy);
  auto sight = scene->getComponent<Sight>(enemy);
  float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
  return distance < sight->sight ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
}

AttackPlayer::AttackPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
    : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene) {}

BT::PortsList AttackPlayer::providedPorts() {
  return {};
}

BT::NodeStatus AttackPlayer::tick() {
  auto enemyAttack = scene->getComponent<Attack>(enemy)->attack;
  auto playerHp = &scene->getComponent<Hp>(player)->hp;
  *playerHp -= enemyAttack;
  CombatLog::addLog(std::stringstream() << "-----" << scene->getComponent<Name>(enemy)->name << "-----", LogType::COMBAT);
  CombatLog::addLog(std::stringstream() << "player was hit with " << enemyAttack << " damage", LogType::COMBAT);
  CombatLog::addLog(std::stringstream() << "player has " << *playerHp << " hp left", LogType::COMBAT);
  return BT::NodeStatus::SUCCESS;
}

PerformRangedAttack::PerformRangedAttack(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
    : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene) {}

BT::PortsList PerformRangedAttack::providedPorts() {
  return {};
}

BT::NodeStatus PerformRangedAttack::tick() {
  auto enemyAttack = scene->getComponent<RangedAttack>(enemy)->damage;
  auto playerHp = &scene->getComponent<Hp>(player)->hp;
  *playerHp -= enemyAttack;
  CombatLog::addLog(std::stringstream() << "-----" << scene->getComponent<Name>(enemy)->name << "-----", LogType::COMBAT);
  CombatLog::addLog(std::stringstream() << "player was hit with " << enemyAttack << " damage", LogType::COMBAT);
  CombatLog::addLog(std::stringstream() << "player has " << *playerHp << " hp left", LogType::COMBAT);
  return BT::NodeStatus::SUCCESS;
}

ApproachPlayer::ApproachPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
    : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene) {}
BT::PortsList ApproachPlayer::providedPorts() {
  return {};
}
BT::NodeStatus ApproachPlayer::tick() {
  auto playerPos = &scene->getComponent<Position>(player)->pos;
  auto enemyPos = &scene->getComponent<Position>(enemy)->pos;
  auto distance = sf::Vector2i(playerPos->x - enemyPos->x, playerPos->y - enemyPos->y);
  bool hor = abs(distance.x) > abs(distance.y);
  if (hor) {
    if (distance.x > 0) {
      *enemyPos += sf::Vector2i(1, 0);
    } else if (distance.x < 0) {
      *enemyPos += sf::Vector2i(-1, 0);
    }
  } else {
    if (distance.y > 0) {
      *enemyPos += sf::Vector2i(0, 1);
    } else if (distance.y < 0) {
      *enemyPos += sf::Vector2i(0, -1);
    }
  }

  return BT::NodeStatus::SUCCESS;
}
#pragma once

#include <memory>

#include "CombatLog.hpp"
#include "Scene.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include "component/ActorComponent.hpp"
#include "component/TraitComponent.hpp"

class InSight : public BT::ConditionNode {
 public:
  InSight(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::ConditionNode(name, config), player(player), enemy(enemy), scene(scene) {}

  static BT::PortsList providedPorts() {
    return {};
  }

  BT::NodeStatus tick() override {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    float sight = scene->getComponent<Sight>(enemy)->sight;
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < sight + 0.1f ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  }

  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

// next to meaning "adjacent to", even diagonally
class IsNextToPlayer : public BT::ConditionNode {
 public:
  IsNextToPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::ConditionNode(name, config), player(player), enemy(enemy), scene(scene){};
  static BT::PortsList providedPorts() {
    return {};
  };
  BT::NodeStatus tick() override {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    return abs(playerPos->pos.x - enemyPos->pos.x) <= 1 && abs(playerPos->pos.y - enemyPos->pos.y) <= 1 ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  };
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

// usage prerequisite: Action has a field called "range"
template <class RangedAction>
class InRangeGeneric : public BT::ConditionNode {
 public:
  InRangeGeneric(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::ConditionNode(name, config), player(player), enemy(enemy), scene(scene){};

  static BT::PortsList providedPorts() {
    return {};
  };

  BT::NodeStatus tick() override {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    float range = scene->getComponent<RangedAction>(enemy)->range;
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < range + 0.1f ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  }

  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class Wander : public BT::SyncActionNode {
 public:
  Wander(const std::string& name, const BT::NodeConfig& config, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::SyncActionNode(name, config), enemy(enemy), scene(scene) {}

  static BT::PortsList providedPorts() {
    return {};
  }

  BT::NodeStatus tick() override {
    auto enemyPos = scene->getComponent<Position>(enemy);
    enemyPos->pos.x += rand() % 3 - 1;
    enemyPos->pos.y += rand() % 3 - 1;
    return BT::NodeStatus::SUCCESS;
  }

  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class AttackPlayer : public BT::SyncActionNode {
 public:
  AttackPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene){};
  static BT::PortsList providedPorts() {
    return {};
  };
  BT::NodeStatus tick() override {
    auto enemyAttack = scene->getComponent<Attack>(enemy)->attack;
    auto playerHp = &scene->getComponent<Hp>(player)->hp;
    *playerHp -= enemyAttack;
    CombatLog::addLog(std::stringstream() << "-----" << scene->getComponent<Name>(enemy)->name << "-----", LogType::COMBAT);
    CombatLog::addLog(std::stringstream() << "player was hit with " << enemyAttack << " damage", LogType::COMBAT);
    CombatLog::addLog(std::stringstream() << "player has " << *playerHp << " hp left", LogType::COMBAT);
    return BT::NodeStatus::SUCCESS;
  };
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class PerformRangedAttack : public BT::SyncActionNode {
 public:
  PerformRangedAttack(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene){};
  static BT::PortsList providedPorts() {
    return {};
  };
  BT::NodeStatus tick() override {
    auto enemyAttack = scene->getComponent<RangedAttack>(enemy)->damage;
    auto playerHp = &scene->getComponent<Hp>(player)->hp;
    *playerHp -= enemyAttack;
    CombatLog::addLog(std::stringstream() << "-----" << scene->getComponent<Name>(enemy)->name << "-----", LogType::COMBAT);
    CombatLog::addLog(std::stringstream() << "player was hit with " << enemyAttack << " damage", LogType::COMBAT);
    CombatLog::addLog(std::stringstream() << "player has " << *playerHp << " hp left", LogType::COMBAT);
    return BT::NodeStatus::SUCCESS;
  };
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class PerformMeleeAttack : public BT::SyncActionNode {
 public:
  PerformMeleeAttack(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene){};
  static BT::PortsList providedPorts() {
    return {};
  };
  BT::NodeStatus tick() override {
    auto enemyAttack = scene->getComponent<MeleeAttack>(enemy)->damage;
    auto playerHp = &scene->getComponent<Hp>(player)->hp;
    *playerHp -= enemyAttack;
    CombatLog::addLog(std::stringstream() << "-----" << scene->getComponent<Name>(enemy)->name << "-----", LogType::COMBAT);
    CombatLog::addLog(std::stringstream() << "player was hit with " << enemyAttack << " damage", LogType::COMBAT);
    CombatLog::addLog(std::stringstream() << "player has " << *playerHp << " hp left", LogType::COMBAT);
    return BT::NodeStatus::SUCCESS;
  };
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class ApproachPlayer : public BT::SyncActionNode {
 public:
  ApproachPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene)
      : BT::SyncActionNode(name, config), player(player), enemy(enemy), scene(scene){};
  static BT::PortsList providedPorts() {
    return {};
  };
  BT::NodeStatus tick() override {
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
  };
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

#pragma once

#include <memory>

#include "CombatLog.hpp"
#include "Scene.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include "component/ActorComponent.hpp"
#include "component/TraitComponent.hpp"

class InSight : public BT::ConditionNode {
 public:
  InSight(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene);
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
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
    auto range = scene->getComponent<RangedAction>(enemy)->range;
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < range ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  }

  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class AttackPlayer : public BT::SyncActionNode {
 public:
  AttackPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene);
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class PerformRangedAttack : public BT::SyncActionNode {
 public:
  PerformRangedAttack(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene);
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

class ApproachPlayer : public BT::SyncActionNode {
 public:
  ApproachPlayer(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene);
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
  EntityID player;
  EntityID enemy;
  std::shared_ptr<Scene> scene;
};

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

class InRange : public BT::ConditionNode {
 public:
  InRange(const std::string& name, const BT::NodeConfig& config, EntityID player, EntityID enemy, std::shared_ptr<Scene> scene);
  static BT::PortsList providedPorts();
  BT::NodeStatus tick() override;
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

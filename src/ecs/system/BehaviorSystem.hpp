#pragma once

#include "Scene.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include "component/ActorComponent.hpp"

class ApproachObject : public BT::SyncActionNode {
 public:
  ApproachObject(const std::string& name, const BT::NodeConfig& config, std::shared_ptr<Scene> scene, EntityID playerID)
      : BT::SyncActionNode(name, config), scene(scene), playerID(playerID) {}

  // You must override the virtual function tick()
  BT::NodeStatus tick() override {
    std::cout << "ApproachObject" << std::endl;
    auto position = scene->getComponent<component::Position>(playerID);
    std::cout << "player pos from tree: " << position->pos.x;
    return BT::NodeStatus::SUCCESS;
  }
  static BT::PortsList providedPorts() {
    return {};
  }
  std::shared_ptr<Scene> scene;
  EntityID playerID;
};

class OpenSth : public BT::SyncActionNode {
 public:
  OpenSth(const std::string& name) : BT::SyncActionNode(name, {}) {}

  // You must override the virtual function tick()
  BT::NodeStatus tick() override {
    std::cout << "OpenSth: " << this->name() << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};
#pragma once

#include "behaviortree_cpp/bt_factory.h"
#include "component/ActorComponent.hpp"

class ApproachObject : public BT::SyncActionNode
{
public:
  ApproachObject(const std::string& name) :
      BT::SyncActionNode(name, {})
  {}

  // You must override the virtual function tick()
  BT::NodeStatus tick() override
  {
    std::cout << "ApproachObject: " << this->name() << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};

class OpenSth : public BT::SyncActionNode
{
public:
  OpenSth(const std::string& name) :
      BT::SyncActionNode(name, {})
  {}

  // You must override the virtual function tick()
  BT::NodeStatus tick() override
  {
    std::cout << "OpenSth: " << this->name() << std::endl;
    return BT::NodeStatus::SUCCESS;
  }
};
#pragma once

#include <bitset>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "component/Component.hpp"

using namespace component;

constexpr size_t MAX_COMPONENTS = 64;
typedef size_t EntityID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

struct Registry {
  std::vector<std::shared_ptr<std::unordered_map<EntityID, std::shared_ptr<Component>>>> components;

  Registry() {
    for (size_t i = 0; i < MAX_COMPONENTS; i++) {
      components.push_back(std::make_shared<std::unordered_map<EntityID, std::shared_ptr<Component>>>());
    }
  }

  template <typename T>
  void addNewComponentType() {
    T::id = Component::componentCount++;
    components.push_back(std::make_shared<std::unordered_map<EntityID, std::shared_ptr<Component>>>());
  }

  template <typename T>
  void addComponent(EntityID id, std::shared_ptr<T> component) {
    // we need to assign proper id if we use the component for the first time
    // id of -1 also tells us that we need to create the map for the component
    // type
    if (T::id == -1) {
      T::id = Component::componentCount++;

      components.push_back(std::make_shared<std::unordered_map<EntityID, std::shared_ptr<Component>>>());
    }

    components.at(T::id)->insert_or_assign(id, component);
  }

  template <typename T>
  void removeComponent(EntityID id) {
    components.at(T::id)->erase(id);
  }

  template <typename T>
  void removeAll() {
    components.at(T::id)->clear();
  }

  void removeComponent(EntityID entityID, int componentID) {
    components.at(componentID)->erase(entityID);
  }
};
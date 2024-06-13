#pragma once

#include <bitset>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Component.hpp"

using namespace component;

constexpr size_t MAX_COMPONENTS = 32;
typedef size_t EntityID;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

struct Registry {
  std::vector<std::shared_ptr<std::unordered_map<EntityID, std::shared_ptr<Component> > > > components;

  template <typename T>
  void addComponent(EntityID id, std::shared_ptr<T> component) {
    // we need to assign proper id if we use the component for the first time
    // id of -1 also tells us that we need to create the map for the component
    // type
    if (T::id == -1) {
      T::id = components.size();

      components.push_back(std::make_shared<std::unordered_map<EntityID, std::shared_ptr<Component> > >());
    }

    components.at(T::id)->insert({id, component});
  }

  template <typename T>
  void removeComponent(EntityID id) {
    components.at(T::id)->erase(id);
  }
};
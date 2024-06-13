#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

// #include "Entity.hpp"
#include "Registry.hpp"

class Scene {
 public:
  Scene();
  EntityID createEntity();
  std::shared_ptr<ComponentMask> getEntityComponents(EntityID id);

  template <typename T>
  Scene& addComponent(EntityID entityID, std::shared_ptr<T> component) {
    // adding component also sets the id for it if it's the first one of its
    // kind
    registry.addComponent(entityID, component);
    // updating the info about components possesed by the entity
    entities.at(entityID)->set(T::id);
    return *this;
  }

  template <typename T>
  void removeComponent(EntityID entityID) {
    if ((*entities.at(entityID))[T::id]) {
      entities.at(entityID)->set(T::id, false);

      registry.removeComponent<T>(entityID);
    }
  }

  template <typename T>
  std::unordered_map<EntityID, std::shared_ptr<T> >& getComponents() {
    return *std::reinterpret_pointer_cast<std::unordered_map<EntityID, std::shared_ptr<T> > >(
        registry.components.at(T::id));
  }

  template <typename T>
  std::shared_ptr<T> getComponent(EntityID id) {
    // I've just commited a coding war crime, fight me
    return std::reinterpret_pointer_cast<T>(registry.components.at(T::id)->at(id));
  }

  std::string getDescription(EntityID entityID, int componentID) {
    return registry.components.at(componentID)->at(entityID)->getDescription();
  }

  template <typename T>
  bool entityHasComponent(EntityID entityID) {
    return (*entities.at(entityID))[T::id];
  }

  Registry registry;
  std::unordered_map<EntityID, std::shared_ptr<ComponentMask> > entities;

 private:
  unsigned long entityCount;
};
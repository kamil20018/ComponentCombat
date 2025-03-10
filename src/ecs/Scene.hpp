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
  void initComponents();

  template <typename T>
  Scene &addComponent(EntityID entityID, std::shared_ptr<T> component) {
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
  void removeAll() {
    std::vector<EntityID> entitiesToRemove;
    for (auto &[entityID, _] : getComponents<T>()) {
      entitiesToRemove.push_back(entityID);
    }

    for (auto entityID : entitiesToRemove) {
      removeComponent<T>(entityID);
    }
  }

  template <typename T>
  void applyEffect(EntityID origin, EntityID target) {
    addComponent(target, getComponent<T>(origin)->apply());
  }

  void removeEntity(EntityID entityID);

  template <class... Types>
  Scene &addComponents(EntityID entityID, Types &&...components) {
    (
        [&] {
          registry.addComponent(entityID, components);
          entities.at(entityID)->set(components->id);
        }(),
        ...);
    return *this;
  }

  template <typename T>
  std::unordered_map<EntityID, std::shared_ptr<T>> &getComponents() {
    if (T::id == -1) {
      registry.addNewComponentType<T>();
    }
    return *std::reinterpret_pointer_cast<std::unordered_map<EntityID, std::shared_ptr<T>>>(registry.components.at(T::id));
  }

  template <typename T>
  std::shared_ptr<T> getComponent(EntityID id) {
    if (!registry.components.at(T::id)->contains(id)) {
      std::cout << "ERROR: component " << T::componentName << " not found on entity " << id << std::endl;
      std::cout << "entity has components: " << std::endl;
      std::cout << std::setw(4) << getEntitySave(id) << std::endl;
    }
    // I've just commited a coding war crime, fight me
    return std::reinterpret_pointer_cast<T>(registry.components.at(T::id)->at(id));
  }

  std::string getDescription(EntityID entityID, int componentID) {
    return registry.components.at(componentID)->at(entityID)->getDescription();
  }

  /// @brief Calls the `serialize` method on the specified component
  json getComponentSave(EntityID entityID, int componentID) {
    return registry.components.at(componentID)->at(entityID)->serialize();
  }

  json getEntitySave(EntityID entityID) {
    json entitySave;
    auto components = getEntityComponents(entityID);
    for (size_t i = 0; i < MAX_COMPONENTS; i++) {
      bool hasComponent = (*components)[i];
      if (hasComponent) {
        entitySave.update(getComponentSave(entityID, i));
      }
    }
    return entitySave;
  }

  template <typename T>
  bool entityHasComponent(EntityID entityID) {
    return (*entities.at(entityID))[T::id];
  }

  Registry registry;
  std::unordered_map<EntityID, std::shared_ptr<ComponentMask>> entities;

 private:
  unsigned long entityCount;
};
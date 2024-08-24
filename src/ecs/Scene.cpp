#include "Scene.hpp"

Scene::Scene() : entityCount(-1){};

EntityID Scene::createEntity() {
  EntityID id = ++entityCount;
  entities.insert({id, std::make_shared<ComponentMask>()});
  return id;
}

void Scene::removeEntity(EntityID entityID) {
  for (int componentID = 0; componentID < MAX_COMPONENTS; componentID++) {
    if ((*getEntityComponents(entityID))[componentID]) {
      registry.removeComponent(entityID, componentID);
    }
  }

  entities.erase(entityID);
}

std::shared_ptr<ComponentMask> Scene::getEntityComponents(EntityID id) {
  return entities.at(id);
}

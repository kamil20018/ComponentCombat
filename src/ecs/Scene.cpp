#include "Scene.hpp"

Scene::Scene() : entityCount(-1){};

EntityID Scene::createEntity() {
  EntityID id = ++entityCount;
  entities.insert({id, std::make_shared<ComponentMask>()});
  return id;
}

std::shared_ptr<ComponentMask> Scene::getEntityComponents(EntityID id) { return entities.at(id); }
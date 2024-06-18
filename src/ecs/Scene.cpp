#include "Scene.hpp"

Scene::Scene() : entityCount(-1) { initComponents(); };

EntityID Scene::createEntity() {
  EntityID id = ++entityCount;
  entities.insert({id, std::make_shared<ComponentMask>()});
  return id;
}

std::shared_ptr<ComponentMask> Scene::getEntityComponents(EntityID id) { return entities.at(id); }

void Scene::initComponents() {
  EntityID filler = createEntity();
  addComponent(filler, std::make_shared<Position>(0, 0));
  addComponent(filler, std::make_shared<Size>(0, 0));
  addComponent(filler, std::make_shared<Hp>(0));
  addComponent(filler, std::make_shared<Poisoned>(0, 0));
  addComponent(filler, std::make_shared<BodyColor>(sf::Color::Black));
}

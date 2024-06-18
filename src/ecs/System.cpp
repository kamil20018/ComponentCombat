#include "System.hpp"

#define iter(name, compType) for (auto &[name##ID, name##Component] : scene->getComponents<compType>())
#define if_has(entity, compType) if (scene->entityHasComponent<compType>(entity))
System::System(std::shared_ptr<Scene> scene) : scene(scene){};

void System::applyPoison() {
  std::cout << "applyPoison" << std::endl;

  std::vector<EntityID> removables;

  iter(poisoned, component::Poisoned) {
    if_has(poisonedID, component::Hp) {
      std::cout << poisonedID << " has Poisoned Component, damage: " << poisonedComponent->damage
                << " duration: " << poisonedComponent->duration << std::endl;
      scene->getComponent<component::Hp>(poisonedID)->hp -= poisonedComponent->damage;
    }
    // if something w/o hp got poisoned we want to remove the poisoned effect
    // anyway
    poisonedComponent->duration--;
    if (poisonedComponent->duration == 0) {
      removables.push_back(poisonedID);
    }
  }

  for (auto removable : removables) {
    scene->removeComponent<component::Poisoned>(removable);
  }
}

void System::drawComponents(sf::Vector2i mousePos) {
  for (auto &[entityID, position] : scene->getComponents<component::Position>()) {
    if (scene->entityHasComponent<component::Size>(entityID)) {
      auto size = scene->getComponent<component::Size>(entityID);
      if (position->x * TILE_SIZE < mousePos.x && mousePos.x < position->x * TILE_SIZE + size->width &&
          position->y * TILE_SIZE < mousePos.y && mousePos.y < position->y * TILE_SIZE + size->height) {
        if (ImGui::Begin("Debug component list", NULL,
                         ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
          auto components = scene->getEntityComponents(entityID);
          for (int i = 0; i < MAX_COMPONENTS; i++) {
            bool hasComponent = (*components)[i];
            if (hasComponent) {
              ImGui::Text(scene->getDescription(entityID, i).c_str());
            }
          }
        }
        ImGui::End();
        return;
      }
    }
  }
}

void System::drawEntities(std::shared_ptr<sf::RenderWindow> window) {
  for (auto &[entityID, bodyColor] : scene->getComponents<component::BodyColor>()) {
    if (scene->entityHasComponent<component::Position>(entityID) &&
        scene->entityHasComponent<component::Size>(entityID)) {
      auto position = scene->getComponent<component::Position>(entityID);
      auto size = scene->getComponent<component::Size>(entityID);
      sf::RectangleShape rectangle(sf::Vector2f(size->width, size->height));
      rectangle.setFillColor(bodyColor->color);
      rectangle.setPosition(position->x * TILE_SIZE, position->y * TILE_SIZE);
      window->draw(rectangle);
    }
  }
}

void System::debugPrint() {
  for (auto &[entityID, hpComponent] : scene->getComponents<Hp>()) {
    std::cout << entityID << " hp: " << hpComponent->hp << std::endl;
  }
}
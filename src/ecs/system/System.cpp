#include "System.hpp"

#define iter(name, compType) for (auto &[name##ID, name##Component] : scene->getComponents<compType>())
#define if_has(entity, compType) if (scene->entityHasComponent<compType>(entity))
System::System(std::shared_ptr<Scene> scene) : scene(scene){};

void System::moveEntity(EntityID entityID, sf::Vector2i moveBy) {
  if_has(entityID, component::Position) {
    auto entityPos = scene->getComponent<component::Position>(entityID);
    entityPos->pos += moveBy;
  }
}

void System::drawComponents(sf::Vector2i mousePos) {
  for (auto &[entityID, position] : scene->getComponents<component::Position>()) {
    if (position->pos.x == mousePos.x && position->pos.y == mousePos.y) {
      ImGui::SetNextWindowPos(ImVec2(std::max(ImGui::GetMousePos().x - 200.0f, 0.0f), ImGui::GetMousePos().y + 5.0f));
      if (ImGui::Begin("Debug component list", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        auto components = scene->getEntityComponents(entityID);
        for (size_t i = 0; i < MAX_COMPONENTS; i++) {
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

void System::drawEntities(std::shared_ptr<sf::RenderWindow> window, std::unordered_map<sf::Vector2i, ShaderType, Vector2iHash> activeShaders) {
  for (auto &[entityID, bodyColor] : scene->getComponents<component::BodyColor>()) {
    if (scene->entityHasComponent<component::Position>(entityID) && scene->entityHasComponent<component::Size>(entityID)) {
      auto position = scene->getComponent<component::Position>(entityID);
      auto size = scene->getComponent<component::Size>(entityID);
      sf::RectangleShape rectangle(sf::Vector2f(size->width, size->height));
      rectangle.setFillColor(bodyColor->color);
      rectangle.setPosition(position->pos.x * TILE_SIZE, position->pos.y * TILE_SIZE);
      if (activeShaders.contains(position->pos)) {
        ShaderManager::shaders[activeShaders[position->pos]].setUniform("u_time", ShaderManager::shaderClock.getElapsedTime().asSeconds());
        ShaderManager::shaders[activeShaders[position->pos]].setUniform("u_resolution", sf::Glsl::Vec2{40, 40});
        window->draw(rectangle, &ShaderManager::shaders[activeShaders[position->pos]]);
        std::cout << "in if" << position->pos.x << " " << position->pos.y << std::endl;
      } else {
        window->draw(rectangle);
      }
    }
  }
}

void System::debugPrint() {
  for (auto &[entityID, hpComponent] : scene->getComponents<Hp>()) {
    std::cout << entityID << " hp: " << hpComponent->hp << std::endl;
  }
}

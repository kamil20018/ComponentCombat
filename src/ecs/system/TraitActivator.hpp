#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Constants.hpp"
#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "Scene.hpp"
#include "ShaderManager.hpp"
#include "component/ActorComponent.hpp"
#include "component/EntityComponent.hpp"
#include "component/TraitComponent.hpp"

struct Vector2iHash {
  std::size_t operator()(const sf::Vector2i& v) const {
    return std::hash<int>{}(v.x) ^ std::hash<int>{}(v.y);
  }
};

class TraitActivator {
 public:
  TraitActivator(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context, std::shared_ptr<sf::RenderWindow> window);
  void drawActiveSkill(std::optional<EntityID> selectedSkill, EntityID player, sf::Vector2i mouseTilePos) {
    if (selectedSkill.has_value()) {
      if (scene->entityHasComponent<MeleeAttack>(selectedSkill.value())) {
        auto meleeAttack = scene->getComponent<MeleeAttack>(selectedSkill.value());
        showMeeleAttack(player, mouseTilePos);
        return;
      }
      if (scene->entityHasComponent<RangedAttack>(selectedSkill.value())) {
        auto rangedAttack = scene->getComponent<RangedAttack>(selectedSkill.value());
        showRangedDefault(player, mouseTilePos, rangedAttack->range);
        return;
      }
    }
  }

  void clearActiveShaders() {
    activeShaders.clear();
  }
  std::unordered_map<sf::Vector2i, ShaderType, Vector2iHash> activeShaders;

 private:
  void showMeeleAttack(EntityID player, sf::Vector2i mouseTilePos);
  void showRangedDefault(EntityID player, sf::Vector2i mouseTilePos, int range);
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;
  std::shared_ptr<sf::RenderWindow> window;
  // std::unordered_map<std::string, std::
};

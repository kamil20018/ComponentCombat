#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Constants.hpp"
#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "Scene.hpp"
#include "component/ActorComponent.hpp"
#include "component/EntityComponent.hpp"
#include "component/TraitComponent.hpp"
class TraitActivator {
 public:
  TraitActivator(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context, std::shared_ptr<sf::RenderWindow> window);
  void drawActiveSkill(std::optional<EntityID> selectedSkill, EntityID player, sf::Vector2i mouseTilePos) {
    if (selectedSkill.has_value()) {
      if (scene->entityHasComponent<MeleeAttack>(selectedSkill.value())) {
        auto meleeAttack = scene->getComponent<MeleeAttack>(selectedSkill.value());
        showAttack(meleeAttack->rangeType, player, mouseTilePos);
        return;
      }
      if (scene->entityHasComponent<RangedAttack>(selectedSkill.value())) {
        auto rangedAttack = scene->getComponent<RangedAttack>(selectedSkill.value());
        showAttack(rangedAttack->rangeType, player, mouseTilePos);
        return;
      }
    }
  }

 private:
  void showAttack(RangeType rangeType, EntityID player, sf::Vector2i mouseTilePos);
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;
  std::shared_ptr<sf::RenderWindow> window;
  // std::unordered_map<std::string, std::
};

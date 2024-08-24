#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "ItemComponent.hpp"
#include "Scene.hpp"

struct EquippedItems {
  std::optional<EntityID> helmet;
  std::optional<EntityID> armour;
  std::optional<EntityID> weapon;
  std::optional<EntityID> pants;
  std::optional<EntityID> boots;
  std::vector<EntityID> getEquippedItems() {
    std::vector<EntityID> items;
    if (helmet) items.push_back(helmet.value());
    if (armour) items.push_back(armour.value());
    if (weapon) items.push_back(weapon.value());
    if (pants) items.push_back(pants.value());
    if (boots) items.push_back(boots.value());
    return items;
  }
};

/// @brief Handles ui rendering along with it's interactions with the ecs
class UiSystem {
 public:
  UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context);

  void handleCharacterScreen(EquippedItems equippedItems);
  void handleInventory(std::vector<EntityID> &inventory, EquippedItems &equippedItems);

 private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;

  void showItemPopup(EntityID id);
};

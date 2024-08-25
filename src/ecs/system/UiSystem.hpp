#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>

#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "ItemComponent.hpp"
#include "Scene.hpp"

struct EquippedItems {
  EquippedItems(){};
  EquippedItems(json j) {
    if (j.contains("helmet")) helmet = j["helmet"];
    if (j.contains("armour")) armour = j["armour"];
    if (j.contains("weapon")) weapon = j["weapon"];
    if (j.contains("pants")) pants = j["pants"];
    if (j.contains("boots")) boots = j["boots"];
  };
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
  json saveEquippedItems(EquippedItems equippedItems);
  json saveItem(EntityID entityID);

  void loadEquippedItems(json &j, EquippedItems &equippedItems);
  void loadItem(json &j, EntityID entityID);

 private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;

  void showItemPopup(EntityID id);
};

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>

#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "Scene.hpp"
#include "component/ItemComponent.hpp"
#include "component/TraitComponent.hpp"

constexpr int SLOT_CAP = 10;  // theoretical endgame cap

typedef std::vector<EntityID> Inventory;

struct EquippedItems {
  EquippedItems(std::shared_ptr<Scene> scene) : scene(scene){};
  EquippedItems(std::shared_ptr<Scene> scene, json j)
      : scene(scene){
            // if (j.contains("helmet")) helmet = j["helmet"];
            // if (j.contains("armour")) armour = j["armour"];
            // if (j.contains("weapon")) weapon = j["weapon"];
            // if (j.contains("pants")) pants = j["pants"];
            // if (j.contains("boots")) boots = j["boots"];
        };

  std::string getTextureName(int slot) {
    if (itemVec.at(slot)) return scene->getComponent<TextureName>(itemVec.at(slot).value())->textureName;
    return image::other::TRANSPARENT;
  }
  std::vector<std::optional<EntityID>> itemVec{std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt};
  std::shared_ptr<Scene> scene;
};

/// @brief Handles ui rendering along with it's interactions with the ecs
class UiSystem {
 public:
  UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context);

  void handleCharacterScreen(EquippedItems &equippedItems, Inventory &inventory);
  void handleInventory(std::vector<EntityID> &inventory, EquippedItems &equippedItems);

  json saveEquippedItems(EquippedItems equippedItems);
  void loadEquippedItems(json &j, EquippedItems &equippedItems);

  json saveInventory(Inventory inventory);
  void loadInventory(json &j, Inventory &inventory);

  json saveItem(EntityID entityID);
  void loadItem(json &j, EntityID entityID);

 private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;

  void showItemPopup(EntityID id);
};

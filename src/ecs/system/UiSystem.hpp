#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>

#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "Scene.hpp"
#include "component/EntityComponent.hpp"
#include "component/TraitComponent.hpp"
#include "system/TraitActivator.hpp"

namespace fs = std::filesystem;

constexpr int SLOT_CAP = 10;  // theoretical endgame cap, for skills

typedef std::vector<EntityID> Inventory;

struct EquippedItems {
  EquippedItems(std::shared_ptr<Scene> scene) : scene(scene){};
  EquippedItems(std::shared_ptr<Scene> scene, json j) : scene(scene){};

  std::string getTextureName(size_t slot) {
    if (slot >= itemVec.size() || !itemVec.at(slot)) return image::other::TRANSPARENT;
    return scene->getComponent<TextureName>(itemVec.at(slot).value())->textureName;
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
  void handleActiveSkillBar(EquippedItems &equippedItems);
  std::optional<EntityID> getSelectedSkill();

  json saveEquippedItems(EquippedItems equippedItems);
  void loadEquippedItems(json &j, EquippedItems &equippedItems);

  json saveInventory(Inventory inventory);
  void loadInventory(json &j, Inventory &inventory);

  void loadBoughtTraits(json boughtTraits, Inventory &inventory);

  json saveItem(EntityID entityID);
  void loadItem(json &j, EntityID entityID);

 private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;
  json traitsJson;
  std::optional<EntityID> selectedSkill;
  void showItemPopup(EntityID id);
};

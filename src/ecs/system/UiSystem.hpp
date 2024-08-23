#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Context.hpp"
#include "Scene.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"

#include "ItemComponent.hpp"

struct EquippedItems {
  std::optional<EntityID> helmet;
  std::optional<EntityID> armour;
  std::optional<EntityID> weapon;
  std::optional<EntityID> pants;
  std::optional<EntityID> boots;
};

/// @brief Handles ui rendering along with it's interactions with the ecs
class UiSystem {
public:
  UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context);

  void handleCharacterScreen(EquippedItems equippedItems);
  void handleInventory(const std::vector<EntityID> &inventory);
private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;

  void showItemPopup(EntityID id);
};

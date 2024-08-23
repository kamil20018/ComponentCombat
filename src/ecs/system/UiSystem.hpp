#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "Context.hpp"
#include "Scene.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"

/// @brief Handles ui rendering along with it's interactions with the ecs
class UiSystem {
public:
  UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context);

  void handleCharacterScreen();
void handleInventory();
private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;
};

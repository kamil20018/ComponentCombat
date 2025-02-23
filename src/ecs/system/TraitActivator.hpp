#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Context.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "Scene.hpp"
#include "component/EntityComponent.hpp"
#include "component/TraitComponent.hpp"
class TraitActivator {
 public:
  TraitActivator(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context);
  void activateTrait(EntityID traitID);

 private:
  std::shared_ptr<Scene> scene;
  std::shared_ptr<Context> context;
  // std::unordered_map<std::string, std::
}
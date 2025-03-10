#pragma once

#include <SFML/Graphics.hpp>

#include "CombatLog.hpp"
#include "Constants.hpp"
#include "Scene.hpp"
#include "component/ActorComponent.hpp"
#include "component/EffectComponent.hpp"
#include "component/TraitComponent.hpp"

using namespace component;

class EffectSystem {
 public:
  EffectSystem(std::shared_ptr<Scene> scene);
  void updateEffectStatuses();

 private:
  void applyMeeleDamage();
  void applyRangedDamage();
  std::shared_ptr<Scene> scene;
};
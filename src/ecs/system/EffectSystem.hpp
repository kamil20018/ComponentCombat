#pragma once

#include <SFML/Graphics.hpp>
#include <random>

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
  void resetAppliedThisTurn();

  void outgoingMeeleDamage(EntityID origin, EntityID target, MeeleDamage meeleDamage);
  void outgoingRangedDamage(EntityID origin, EntityID target, RangedDamage rangedDamage);
  void createPoisonEffect(EntityID origin, EntityID target, std::shared_ptr<PoisonBody> poisonEffect, float baseDamage);
  void applyMeeleDamage(EntityID target);
  void applyRangedDamage(EntityID target);

 private:
  void applyPoison();
  std::shared_ptr<Scene> scene;
  std::default_random_engine e1;
  std::uniform_real_distribution<float> float_dist;
};
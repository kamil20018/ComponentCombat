#include "EffectSystem.hpp"

#define iter(name, compType) for (auto &[name##ID, name##Component] : scene->getComponents<compType>())
#define if_has(entity, compType) if (scene->entityHasComponent<compType>(entity))

EffectSystem::EffectSystem(std::shared_ptr<Scene> scene) : scene(scene){};

void EffectSystem::updateEffectStatuses() {
  applyMeeleDamage();
  applyRangedDamage();
}

void EffectSystem::applyMeeleDamage() {
  for (auto &[entityID, meeleDamage] : scene->getComponents<MeeleDamage>()) {
    CombatLog::addLog(meeleDamage->getDescription(), LogType::COMBAT);
    if (scene->entityHasComponent<Hp>(entityID)) {
      scene->getComponent<Hp>(entityID)->hp -= meeleDamage->meeleDamage;
    }
  }
  scene->removeAll<MeeleDamage>();
}

void EffectSystem::applyRangedDamage() {
  for (auto &[entityID, rangedDamage] : scene->getComponents<RangedDamage>()) {
    CombatLog::addLog(rangedDamage->getDescription(), LogType::COMBAT);
    if (scene->entityHasComponent<Hp>(entityID)) {
      scene->getComponent<Hp>(entityID)->hp -= rangedDamage->rangedDamage;
    }
  }
  scene->removeAll<RangedDamage>();
}
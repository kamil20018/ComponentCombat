#include "EffectSystem.hpp"

#define iter(name, compType) for (auto &[name##ID, name##Component] : scene->getComponents<compType>())
#define if_has(entity, compType) if (scene->entityHasComponent<compType>(entity))

EffectSystem::EffectSystem(std::shared_ptr<Scene> scene) : scene(scene), e1(std::random_device()()), float_dist(0.0, 1.0){};

// void EffectSystem::updateEffectStatuses() {
//   applyMeeleDamage();
//   applyRangedDamage();
// }

// outgoing meele damage

void EffectSystem::outgoingMeeleDamage(EntityID origin, EntityID target, MeeleDamage meeleDamage) {
  if (scene->entityHasComponent<AllDamageMulti>(origin)) {
    meeleDamage.meeleDamage *= 1.0 + scene->getComponent<AllDamageMulti>(origin)->percentage / 100.0;
  }

  scene->addComponent(target, std::make_shared<MeeleDamage>(meeleDamage));

  if (scene->entityHasComponent<PoisonBody>(origin)) {
    createPoisonEffect(origin, target, scene->getComponent<PoisonBody>(origin), meeleDamage.meeleDamage);
  }
  applyMeeleDamage(target);
}

void EffectSystem::outgoingRangedDamage(EntityID origin, EntityID target, RangedDamage rangedDamage) {
  if (scene->entityHasComponent<AllDamageMulti>(origin)) {
    rangedDamage.rangedDamage *= 1.0 + scene->getComponent<AllDamageMulti>(origin)->percentage / 100.0;
  }

  scene->addComponent(target, std::make_shared<RangedDamage>(rangedDamage));

  if (scene->entityHasComponent<PoisonBody>(origin)) {
    createPoisonEffect(origin, target, scene->getComponent<PoisonBody>(origin), rangedDamage.rangedDamage);
  }
  applyRangedDamage(target);
}

void EffectSystem::createPoisonEffect(EntityID origin, EntityID target, std::shared_ptr<PoisonBody> poisonBody, float baseDamage) {
  if (float_dist(e1) < poisonBody->procChance) {
    scene->addComponent<PoisonEffect>(target, std::make_shared<PoisonEffect>(poisonBody->duration, poisonBody->damagePercent / 100 * baseDamage));
    CombatLog::addLog("Poison effect applied", LogType::COMBAT);
  } else {
    CombatLog::addLog("Poison effect resisted", LogType::COMBAT);
  }
}

void EffectSystem::applyMeeleDamage(EntityID target) {
  auto meeleDamage = scene->getComponent<MeeleDamage>(target);
  CombatLog::addLog(meeleDamage->getDescription(), LogType::COMBAT);
  if (scene->entityHasComponent<Hp>(target)) {
    scene->getComponent<Hp>(target)->hp -= meeleDamage->meeleDamage;
  }

  scene->removeComponent<MeeleDamage>(target);
}

void EffectSystem::applyRangedDamage(EntityID target) {
  auto rangedDamage = scene->getComponent<RangedDamage>(target);
  CombatLog::addLog(rangedDamage->getDescription(), LogType::COMBAT);
  if (scene->entityHasComponent<Hp>(target)) {
    scene->getComponent<Hp>(target)->hp -= rangedDamage->rangedDamage;
  }

  scene->removeComponent<MeeleDamage>(target);
}
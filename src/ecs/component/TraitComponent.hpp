#pragma once

#include <memory>

#include "component/Component.hpp"
#include "component/EffectComponent.hpp"
#include "component/TraitComponentHelpers.hpp"

namespace component {

  struct MeleeAttack : public Component {
    MeleeAttack(float damage) : damage(damage){};
    MeleeAttack(json j) : damage(j["meleeAttack"]["damage"]){};
    json serialize() override {
      return json{{"meleeAttack", {{"damage", damage}}}};
    }

    std::string getDescription() override {
      return (std::stringstream() << "MELEEATTACK | damage: " << damage).str();
    }

    std::shared_ptr<MeeleDamage> apply() {
      return std::make_shared<MeeleDamage>(damage);
    }

    inline static int id = -1;
    inline static std::string componentName = "MeleeAttack";
    inline static RangeType rangeType = RangeType::MELEE_NEIGHBOURING;
    float damage;
  };

  struct RangedAttack : public Component {
    RangedAttack(int range, float damage) : range(range), damage(damage){};
    RangedAttack(json j) : range(j["rangedAttack"]["range"]), damage(j["rangedAttack"]["damage"]){};
    json serialize() override {
      return json{{"rangedAttack", {{"range", range}, {"damage", damage}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "RANGEDATTACK | range: " << range << ", damage: " << damage).str();
    }

    std::shared_ptr<RangedDamage> apply() {
      return std::make_shared<RangedDamage>(damage);
    }

    inline static int id = -1;
    inline static std::string componentName = "RangedAttack";
    inline static RangeType rangeType = RangeType::RANGED_DEFAULT;
    int range;
    float damage;
  };

  struct Hp : public Component {
    Hp(int hp) : hp(hp){};
    Hp(const json &j) : hp(j["hp"]){};
    json serialize() override {
      return json{{"hp", hp}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "HP | Hp: " << hp).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "Hp";
    int hp;
  };

}  // namespace component
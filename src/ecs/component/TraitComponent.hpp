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

    MeeleDamage getEffect() {
      return MeeleDamage(damage);
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

    RangedDamage getEffect() {
      return RangedDamage(damage);
    }

    inline static int id = -1;
    inline static std::string componentName = "RangedAttack";
    inline static RangeType rangeType = RangeType::RANGED_DEFAULT;
    int range;
    float damage;
  };

  struct PoisonBody : public Component {
    PoisonBody(float procChance, float damagePercent, int duration) : procChance(procChance), damagePercent(damagePercent), duration(duration){};
    PoisonBody(json j) : procChance(j["poisonBody"]["procChance"]), damagePercent(j["poisonBody"]["damagePercent"]), duration(j["poisonBody"]["duration"]){};
    json serialize() override {
      return json{{"poisonBody", {{"procChance", procChance}, {"damagePercent", damagePercent}, {"duration", duration}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POISONBODY | procChance: " << procChance << ", damagePercent: " << damagePercent << ", duration: " << duration).str();
    }

    std::shared_ptr<PoisonEffect> apply() {
      return std::make_shared<PoisonEffect>(duration, damagePercent);
    }

    inline static int id = -1;
    inline static std::string componentName = "PoisonBody";
    float procChance;
    float damagePercent;
    int duration;
  };

  struct AllDamageMulti : public Component {
    AllDamageMulti(float percentage) : percentage(percentage){};
    AllDamageMulti(json j) : percentage(j["allDamageMulti"]["percentage"]){};
    json serialize() override {
      return json{{"allDamageMulti", {{"percentage", percentage}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "ALLDAMAGEMULTI | percentage: " << percentage).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "AllDamageMulti";
    float percentage;
    ;
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
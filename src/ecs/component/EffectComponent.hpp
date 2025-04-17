#pragma once

#include "component/Component.hpp"

namespace component {
  struct MeeleDamage : public Component {
    MeeleDamage(float meeleDamage) : meeleDamage(meeleDamage){};
    MeeleDamage(json j) : meeleDamage(j["meeleDamage"]){};
    json serialize() override {
      return json{{"meeleDamage", meeleDamage}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "MEELEDAMAGE | meeleDamage: " << meeleDamage).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "MeeleDamage";
    float meeleDamage;
  };

  struct RangedDamage : public Component {
    RangedDamage(float rangedDamage) : rangedDamage(rangedDamage){};
    RangedDamage(json j) : rangedDamage(j["rangedDamage"]){};
    json serialize() override {
      return json{{"rangedDamage", rangedDamage}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "RANGEDDAMAGE | rangedDamage: " << rangedDamage).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "RangedDamage";
    float rangedDamage;
  };

  struct PoisonEffect : public Component {
    PoisonEffect(int duration, float damage) : duration(duration), damage(damage){};
    PoisonEffect(json j) : duration(j["poisonEffect"]["duration"]), damage(j["poisonEffect"]["damage"]){};
    json serialize() override {
      return json{{"poisonEffect", {{"duration", duration}, {"damage", damage}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POISONEFFECT | duration: " << duration << ", damage: " << damage).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "PoisonEffect";
    int duration;
    float damage;
    bool appliedThisTurn = true;
  };
}  // namespace component
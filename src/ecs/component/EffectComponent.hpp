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
}  // namespace component
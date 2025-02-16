#pragma once

#include "component/Component.hpp"

namespace component {
  struct RangedAttack : public Component {
    RangedAttack(int range, int damage) : range(range), damage(damage){};
    RangedAttack(json j) : range(j["rangedAttack"]["range"]), damage(j["rangedAttack"]["damage"]){};
    json serialize() override {
      return json{{"rangedAttack", {{"range", range}, {"damage", damage}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "RANGEDATTACK | range: " << range << ", damage: " << damage).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "RangedAttack";
    int range;
    int damage;
  };

  struct MeleeAttack : public Component {
    MeleeAttack(int damage) : damage(damage){};
    MeleeAttack(json j) : damage(j["damage"]){};
    json serialize() override {
      return json{{"meleeAttack", {{"damage", damage}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "MELEEATTACK | damage: " << damage).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "MeleeAttack";
    int damage;
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
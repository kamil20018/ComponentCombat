#pragma once

#include "component/Component.hpp"

namespace component {
  /// @brief Serialized to int
  enum class ItemTypes { HELMET, ARMOUR, WEAPON, PANTS, BOOTS, NONE };

  struct ItemType : public Component {
    ItemType(ItemTypes itemType) : itemType(itemType){};
    ItemType(const json &j) : itemType(static_cast<ItemTypes>(j["itemType"])){};
    json serialize() override {
      return json{{"itemType", static_cast<int>(itemType)}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "Item type | " << static_cast<int>(itemType)).str();
    }
    inline static int id = -1;
    ItemTypes itemType;
  };

  struct TextureName : public Component {
    TextureName(std::string textureName) : textureName(textureName){};
    TextureName(const json &j) : textureName(j["textureName"]){};
    json serialize() override {
      return json{{"textureName", textureName}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "ItemTexture | " << textureName).str();
    }
    inline static int id = -1;
    std::string textureName;
  };

  struct AttackRange : public Component {
    AttackRange(float min, float max) : min(min), max(max){};
    AttackRange(const json &j) : min(j["attackRange"]["min"]), max(j["attackRange"]["max"]){};
    json serialize() override {
      return json{{"attackRange", {{"min", min}, {"max", max}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "AttackRange | min: " << min << " max: " << max).str();
    }
    inline static int id = -1;
    float min, max;
  };

  struct Defense : public Component {
    Defense(float defense) : defense(defense){};
    Defense(const json &j) : defense(j["defense"]){};
    json serialize() override {
      return json{{"defense", defense}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "Defense | defense: " << defense).str();
    }
    inline static int id = -1;
    float defense;
  };
  /// @brief Flat attack bonus applying to both ends of the attack range
  struct AttackBonus : public Component {
    AttackBonus(float attackBonus) : attackBonus(attackBonus){};
    AttackBonus(const json &j) : attackBonus(j["attackBonus"]){};
    json serialize() override {
      return json{{"attackBonus", attackBonus}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "AttackBonus | attackBonus: " << attackBonus).str();
    }
    inline static int id = -1;
    float attackBonus;
  };

  struct Poison : public Component {
    Poison(int damage, int duration) : damage(damage), duration(duration){};
    Poison(const json &j) : damage(j["poison"]["damage"]), duration(j["poison"]["duration"]){};
    json serialize() override {
      return json{{"poison", {{"damage", damage}, {"duration", duration}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POISON | damage: " << damage << ", duration: " << duration).str();
    }
    inline static int id = -1;
    int damage;
    int duration;
  };

}  // namespace component
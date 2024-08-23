#pragma once

#include "Component.hpp"

namespace component {
/// @brief Serialized to int
enum class ItemTypes { HELMET, ARMOR, WEAPON, PANTS, BOOTS, NONE };

struct ItemType : public Component {
  ItemType(ItemTypes type) : type(type){};
  ItemType(json j) : type(static_cast<ItemTypes>(j["ItemType"])){};
  json serialize() override {
    return json{{"ItemType", {static_cast<int>(type)}}};
  }
  std::string getDescription() override {
    return (std::stringstream() << "Item type | " << static_cast<int>(type)).str();
  }
  inline static int id = -1;
  ItemTypes type;
};

struct TextureName : public Component {
  TextureName(std::string textureName) : textureName(textureName){};
  TextureName(json j) : textureName(j["textureName"]){};
  json serialize() override {
    return json{{"textureName", {textureName}}};
  }
  std::string getDescription() override {
    return (std::stringstream() << "ItemTexture | " << textureName).str();
  }
  inline static int id = -1;
  std::string textureName;
};

struct AttackRange : public Component {
  AttackRange(float min, float max) : min(min), max(max){};
  AttackRange(json j) : min(j["min"]), max(j["max"]){};
  json serialize() override {
    return json{{"min", {min}}, {"max", {max}}};
  }
  std::string getDescription() override {
    return (std::stringstream() << "AttackRange | min: " << min << " max: " << max).str();
  }
  inline static int id = -1;
  float min, max;
};

struct Defense : public Component {
  Defense(float defense) : defense(defense){};
  Defense(json j) : defense(j["defense"]){};
  json serialize() override {
    return json{{"defense", {defense}}};
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
  AttackBonus(json j) : attackBonus(j[attackBonus]){};
  json serialize() override {
    return json{{"attackBonus", {attackBonus}}};
  }
  std::string getDescription() override {
    return (std::stringstream() << "AttackBonus | attackBonus: " << attackBonus).str();
  }
  inline static int id = -1;
  float attackBonus;
};


}  // namespace component
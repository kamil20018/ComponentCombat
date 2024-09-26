#pragma once

#include "component/Component.hpp"

using json = nlohmann::json;

namespace component {
  struct Position : public Component {
    Position(sf::Vector2i pos) : pos(pos){};
    Position(json j) : pos(sf::Vector2i(j[0], j[1])){};
    json serialize() override {
      return json{{"position", {pos.x, pos.y}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POSITION | x: " << pos.x << ", y: " << pos.y).str();
    }
    inline static int id = -1;
    sf::Vector2i pos;
  };

  struct Size : public Component {
    Size(int width, int height) : width(width), height(height){};
    Size(json j) : width(j["width"]), height(j["height"]){};
    json serialize() override {
      return json{{"size", {{"width", width}, {"height", height}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "SIZE | width: " << width << ", height: " << height).str();
    }
    inline static int id = -1;
    int width;
    int height;
  };

  struct Hp : public Component {
    Hp(int hp) : hp(hp){};
    Hp(json j) : hp(j["hp"]){};
    json serialize() override {
      return json{{"hp", hp}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "HP | Hp: " << hp).str();
    }
    inline static int id = -1;
    int hp;
  };

  struct Attack : public Component {
    Attack(int attack) : attack(attack){};
    Attack(json j) : attack(j["attack"]){};
    json serialize() override {
      return json{{"attack", attack}};
    }
    std::string getDescription() override;
    inline static int id = -1;
    int attack;
  };

  struct Poisoned : public Component {
    Poisoned(int damage, int duration) : damage(damage), duration(duration){};
    Poisoned(json j) : damage(j["damage"]), duration(j["duration"]){};
    json serialize() override {
      return json{{"damage", damage}, {"duration", duration}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POISONED | damage: " << damage << ", duration: " << duration).str();
    }
    inline static int id = -1;
    int damage;
    int duration;
  };

  struct BodyColor : public Component {
    BodyColor(sf::Color color) : color(color){};
    BodyColor(json j) : color(sf::Color(j["r"], j["g"], j["b"])){};
    json serialize() override {
      return json{{"color",
                   {
                       {"r", color.r},
                       {"g", color.g},
                       {"b", color.b},
                   }}};
    }
    inline static int id = -1;
    sf::Color color;
  };

  struct Name : public Component {
    Name(std::string name) : name(name){};
    Name(json j) : name(j["name"]){};
    json serialize() override {
      return json{{"name", name}};
    }

    std::string getDescription() override {
      return (std::stringstream() << "NAME | name: " << name).str();
    };
    inline static int id = -1;
    std::string name;
  };

  struct Sight : public Component {
    Sight(int sight) : sight(sight){};
    Sight(json j) : sight(j["sight"]){};
    json serialize() override {
      return json{{"sight", sight}};
    }

    std::string getDescription() override {
      return (std::stringstream() << "SIGHT | sight: " << sight).str();
    }
    inline static int id = -1;
    int sight;
  };

  struct Range : public Component {
    Range(int range) : range(range){};
    Range(json j) : range(j["range"]){};
    json serialize() override {
      return json{{"range", range}};
    }

    std::string getDescription() override {
      return (std::stringstream() << "RANGE | range: " << range).str();
    }
    inline static int id = -1;
    int range;
  };
}  // namespace component
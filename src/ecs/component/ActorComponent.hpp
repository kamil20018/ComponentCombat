#pragma once

#include <filesystem>

#include "behaviortree_cpp/bt_factory.h"
#include "component/Component.hpp"
#include "component/ComponentHelpers.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace component {
  struct Position : public Component {
    Position(sf::Vector2i pos) : pos(pos){};
    Position(const json &j) : pos(sf::Vector2i(j["position"][0], j["position"][1])){};
    json serialize() override {
      return json{{"position", {pos.x, pos.y}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POSITION | x: " << pos.x << ", y: " << pos.y).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "Position";
    sf::Vector2i pos;
  };

  struct Size : public Component {
    Size(int width, int height) : width(width), height(height){};
    Size(const json &j) : width(j["size"]["width"]), height(j["size"]["height"]){};
    json serialize() override {
      return json{{"size", {{"width", width}, {"height", height}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "SIZE | width: " << width << ", height: " << height).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "Size";
    int width;
    int height;
  };

  struct Poisoned : public Component {
    Poisoned(int damage, int duration) : damage(damage), duration(duration){};
    Poisoned(const json &j) : damage(j["poisoned"]["damage"]), duration(j["poisoned"]["duration"]){};
    json serialize() override {
      return json{{"poisoned", {{"damage", damage}, {"duration", duration}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "POISONED | damage: " << damage << ", duration: " << duration).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "Poisoned";
    int damage;
    int duration;
  };

  struct BodyColor : public Component {
    BodyColor(sf::Color color) : color(color){};
    BodyColor(const json &j) : color(sf::Color(j["color"]["r"], j["color"]["g"], j["color"]["b"])){};
    json serialize() override {
      return json{{"color",
                   {
                       {"r", color.r},
                       {"g", color.g},
                       {"b", color.b},
                   }}};
    }
    inline static int id = -1;
    inline static std::string componentName = "BodyColor";
    sf::Color color;
  };

  struct Name : public Component {
    explicit Name(std::string name) : name(name){};
    explicit Name(const json &j) : name(j["name"]){};
    json serialize() override {
      return json{{"name", name}};
    }

    std::string getDescription() override {
      return (std::stringstream() << "NAME | name: " << name).str();
    };
    inline static int id = -1;
    inline static std::string componentName = "Name";
    std::string name;
  };

  struct Sight : public Component {
    Sight(int sight) : sight(sight){};
    Sight(const json &j) : sight(j["sight"]){};
    json serialize() override {
      return json{{"sight", sight}};
    }

    std::string getDescription() override {
      return (std::stringstream() << "SIGHT | sight: " << sight).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "Sight";
    int sight;
  };

  struct BehaviorTree : public Component {
    BehaviorTree(BT::BehaviorTreeFactory &&factory, const json &j) : path(j["behaviorTree"]["path"]), type(StringToBtType.at(j["behaviorTree"]["type"])) {
      tree = factory.createTreeFromFile(path);
    };
    BehaviorTree(BT::BehaviorTreeFactory &&factory, fs::path path, BtType type) : path(path), type(type) {
      tree = factory.createTreeFromFile(path);
    };
    json serialize() override {
      return json{{"behaviorTree", {{"type", BtTypeToString.at(static_cast<int>(type))}, {"path", path.string()}}}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "BEHAVIOURTREE | tree: " << BtTypeToString.at(static_cast<int>(type))).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "BehaviorTree";
    BT::Tree tree;
    fs::path path;
    BtType type;
  };
}  // namespace component
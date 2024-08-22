#pragma once

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
using json = nlohmann::json;

namespace component {
struct Component {
  Component(){};
  virtual std::string getDescription() { return "this component has no description"; };
  virtual json serialize() = 0;
  inline static int componentCount = 0;
};

struct Position : public Component {
  Position(sf::Vector2i pos) : pos(pos){};
  Position(json j) : pos(sf::Vector2i(j[0], j[1])){};
  json serialize() override { return json{{"Position", {pos.x, pos.y}}}; }
  std::string getDescription() override { return (std::stringstream() << "POSITION | x: " << pos.x << ", y: " << pos.y).str(); }
  inline static int id = -1;
  sf::Vector2i pos;
};

struct Size : public Component {
  Size(int width, int height) : width(width), height(height){};
  Size(json j) : width(j[0]), height(j[1]){};
  json serialize() override { return json{{"Size", {width, height}}}; }
  std::string getDescription() override { return (std::stringstream() << "SIZE | width: " << width << ", height: " << height).str(); }
  inline static int id = -1;
  int width;
  int height;
};

struct Hp : public Component {
  Hp(int hp) : hp(hp){};
  Hp(json j) : hp(j["Hp"]){};
  json serialize() override { return json{{"Hp", hp}}; }
  std::string getDescription() override { return (std::stringstream() << "HP | Hp: " << hp).str(); }
  inline static int id = -1;
  int hp;
};

struct Attack : public Component {
  Attack(int attack) : attack(attack){};
  Attack(json j) : attack(j["Attack"]){};
  json serialize() override { return json{{"Attack", attack}}; }
  std::string getDescription() override;
  inline static int id = -1;
  int attack;
};

struct Poisoned : public Component {
  Poisoned(int damage, int duration) : damage(damage), duration(duration){};
  Poisoned(json j) : damage(j["Damage"]), duration(j["Duration"]){};
  json serialize() override { return json{{"Damage", damage}, {"Duration", duration}}; }
  std::string getDescription() override { return (std::stringstream() << "POISONED | damage: " << damage << ", duration: " << duration).str(); }
  inline static int id = -1;
  int damage;
  int duration;
};

struct BodyColor : public Component {
  BodyColor(sf::Color color) : color(color){};
  BodyColor(json j) : color(sf::Color(j["R"], j["G"], j["B"])){};
  json serialize() override {
    return json{{"Color",
                 {
                     {"R", color.r},
                     {"G", color.g},
                     {"B", color.b},
                 }}};
  }
  inline static int id = -1;
  sf::Color color;
};

struct Name : public Component {
  Name(std::string name) : name(name){};
  Name(json j) : name(j["name"]){};
  json serialize() override { return json{{"Name", name}}; }

  std::string getDescription() override { return (std::stringstream() << "NAME | name: " << name).str(); };
  inline static int id = -1;
  std::string name;
};
}  // namespace component
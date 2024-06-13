#pragma once

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

namespace component {
struct Component {
  Component();
  virtual std::string getDescription();
  static int componentCount;
};

struct Position : public Component {
  Position(int x, int y);
  static int id;
  int x;
  int y;
  void debugPrint();
  std::string getDescription() override;
};

struct Size : public Component {
  Size(int width, int height);
  static int id;
  int width;
  int height;
  void debugPrint();
  std::string getDescription() override;
};

struct Hp : public Component {
  Hp(int hp);
  static int id;
  int hp;
  void debugPrint();
  std::string getDescription() override;
};

struct Attack : public Component {
  Attack(int attack);
  static int id;
  int attack;
  void debugPrint();
  std::string getDescription() override;
};

struct Poisoned : public Component {
  Poisoned(int damage, int duration);
  static int id;
  int damage;
  int duration;
  void debugPrint();
  std::string getDescription() override;
};

struct BodyColor : public Component {
  BodyColor(sf::Color color);
  static int id;
  sf::Color color;
  void debugPrint();
};
}  // namespace component
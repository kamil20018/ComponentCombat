#include "Component.hpp"

namespace component {
// //we count components from 0
int Component::componentCount = -1;

Component::Component() { componentCount++; }

std::string Component::getDescription() { return "this component has no description"; }

int Position::id = -1;
Position::Position(int x, int y) : x(x), y(y){};
void Position::debugPrint() { std::cout << getDescription() << std::endl; }
std::string Position::getDescription() { return (std::stringstream() << "POSITION | x: " << x << ", y: " << y).str(); }

int Size::id = -1;
Size::Size(int width, int height) : width(width), height(height){};
void Size::debugPrint() { std::cout << getDescription() << std::endl; }
std::string Size::getDescription() {
  return (std::stringstream() << "SIZE | width: " << width << ", height: " << height).str();
}

int Hp::id = -1;
Hp::Hp(int hp) : hp(hp){};
void Hp::debugPrint() { std::cout << getDescription() << std::endl; }
std::string Hp::getDescription() { return (std::stringstream() << "HP | Hp: " << hp).str(); }

int Poisoned::id = -1;
Poisoned::Poisoned(int damage, int duration) : damage(damage), duration(duration){};
void Poisoned::debugPrint() { std::cout << getDescription() << std::endl; }

std::string Poisoned::getDescription() {
  return (std::stringstream() << "POISONED | damage: " << damage << ", duration: " << duration).str();
}

int BodyColor::id = -1;
BodyColor::BodyColor(sf::Color color) : color(color){};
void BodyColor::debugPrint() { printf("Color component"); }
}  // namespace component
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>

#include "Game.h"
#include "State.h"
class MainMenu : public State {
 private:
  std::shared_ptr<Context> context;
  sf::Clock deltaClock;
  sf::Clock shaderClock;
  sf::Shader shader;
  sf::RectangleShape shape;
  sf::Vector2f mousePosition;

 public:
  MainMenu(std::shared_ptr<Context> &context);
  ~MainMenu();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;
};
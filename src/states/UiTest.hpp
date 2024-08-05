#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <iostream>

#include "Game.h"
#include "State.h"
#include "ImGuiHelper.hpp"

class UiTest : public State {
 private:
 sf::Clock deltaClock;
  std::shared_ptr<Context> context;
  void handleWindow();
 public:
  UiTest(std::shared_ptr<Context> &context);
  ~UiTest();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;
};
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <memory>

#include "Game.hpp"
#include "ImGuiHelper.hpp"
#include "ShaderManager.hpp"
#include "State.hpp"

namespace fs = std::filesystem;

class UiTest : public State {
 private:
  sf::Clock deltaClock;
  std::shared_ptr<Context> context;
  ShaderManager shaderManager;
  sf::Clock shaderClock;

 public:
  UiTest(std::shared_ptr<Context> &context);
  ~UiTest();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;
};
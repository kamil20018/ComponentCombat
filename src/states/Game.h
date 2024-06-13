#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "StateManager.h"

#define _window this->context->window
#define _states this->context->states

class StateManager;

struct Context {
  std::unique_ptr<StateManager> states;
  std::shared_ptr<sf::RenderWindow> window;

  Context() {
    states = std::make_unique<StateManager>();
    window = std::make_shared<sf::RenderWindow>();
  }
};

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  std::shared_ptr<Context> context;
};
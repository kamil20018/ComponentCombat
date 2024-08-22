#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include <memory>

#include "AssetManager.h"
#include "Context.h"
#include "ImageLoader.h"
#include "StateManager.h"

#define _window this->context->window
#define _states this->context->states
#define _assets this->context->assets

namespace fs = std::filesystem;

class StateManager;

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  std::shared_ptr<Context> context;
};
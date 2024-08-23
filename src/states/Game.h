#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include <memory>

#include "AssetManager.h"
#include "Context.h"
#include "ImageLoader.h"
#include "StateManager.h"

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
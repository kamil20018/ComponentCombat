#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include <memory>

#include "AssetManager.hpp"
#include "Context.hpp"
#include "ImageLoader.hpp"
#include "StateManager.hpp"

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
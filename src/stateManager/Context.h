#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>

#include "AssetManager.h"
#include "StateManager.h"
namespace fs = std::filesystem;

#define _window this->context->window
#define _states this->context->states
#define _assets this->context->assets

struct Context {
  std::unique_ptr<StateManager> states;
  std::unique_ptr<AssetManager> assets;
  std::shared_ptr<sf::RenderWindow> window;

  fs::path savePath;

  Context() {
    states = std::make_unique<StateManager>();
    assets = std::make_unique<AssetManager>();
    window = std::make_shared<sf::RenderWindow>();
  }
};
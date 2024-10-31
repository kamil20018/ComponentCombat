#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "AssetManager.hpp"
#include "StateManager.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

#define _window context->window
#define _states context->states
#define _assets context->assets

struct Context {
  std::unique_ptr<StateManager> states;
  std::unique_ptr<AssetManager> assets;
  std::shared_ptr<sf::RenderWindow> window;

  fs::path savePath;
  json saveFile;

  Context() {
    states = std::make_unique<StateManager>();
    assets = std::make_unique<AssetManager>();
    window = std::make_shared<sf::RenderWindow>();
  }
};
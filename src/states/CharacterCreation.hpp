#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

#include "Game.hpp"
#include "GamePlay.hpp"
#include "State.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class CharacterCreation : public State {
 private:
  std::shared_ptr<Context> context;
  sf::Clock deltaClock;

 public:
  CharacterCreation(std::shared_ptr<Context>& context);
  ~CharacterCreation();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;
};
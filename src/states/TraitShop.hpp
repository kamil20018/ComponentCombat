#pragma once

#include <SFML/Graphics/Text.hpp>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <vector>

#include "Game.hpp"
#include "GamePlay.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "State.hpp"
namespace fs = std::filesystem;
using json = nlohmann::json;

class TraitShop : public State {
 public:
  TraitShop(std::shared_ptr<Context>& context);
  ~TraitShop();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;

 private:
  void traitShop();  // for generic layout, to be filled by selected type

  void spendEvolutionPoints(int amount);

  json traitsJson;
  std::shared_ptr<Context> context;
  sf::Clock deltaClock;
};
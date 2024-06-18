#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <vector>

#include "Game.h"
#include "Simulation.h"
#include "State.h"
class LoadGame : public State {
 private:
  std::shared_ptr<Context> context;
  sf::Clock deltaClock;

 public:
  LoadGame(std::shared_ptr<Context> &context);
  ~LoadGame();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;

  fs::path createSaveFile();
  void updateSaveFiles();
  std::vector<fs::path> saveFiles;
};
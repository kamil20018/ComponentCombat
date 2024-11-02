#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

#include "CharacterCreation.hpp"
#include "Game.hpp"
#include "GamePlay.hpp"
#include "State.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class LoadGame : public State {
 private:
  std::shared_ptr<Context> context;
  sf::Clock deltaClock;

 public:
  LoadGame(std::shared_ptr<Context>& context);
  ~LoadGame();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;

  void handleCreateSavePopup();
  void handleDeletePopup();
  fs::path createSaveFile(const std::string& saveName);
  void deleteSave(const std::string& saveName);
  void updateSaveFiles();
  bool pressedEnter;   // saves in popup window
  bool pressedEscape;  // cancels in popup window
  int arrowInput;      //-1, 0 or 1
  size_t selectedSaveIndex;
  std::vector<fs::path> saveFiles;
  fs::path baseSavePath;
  fs::path userSavesPath;

  sf::Sprite backgroundSprite;
};
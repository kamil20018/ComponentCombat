#pragma once

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>

#include "ItemComponent.hpp"
#include "Scene.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class SaveManager {
 public:
  static void loadSave(fs::path savePath, std::shared_ptr<Scene> scene);
  static void updateSave(fs::path savePath, std::shared_ptr<Scene> scene);
  inline static json idMapping;

 private:
  static void loadPlayer(json &save, std::shared_ptr<Scene> scene);
  static json savePlayer(std::shared_ptr<Scene> scene);

  static void loadEquippedItems(json &save, std::shared_ptr<Scene> scene);
  static void loadItem(json &save, std::shared_ptr<Scene> scene, EntityID entityID);
  static json saveItem(std::shared_ptr<Scene> scene, EntityID entityID);
  static json saveEquippedItems(std::shared_ptr<Scene> scene);
};

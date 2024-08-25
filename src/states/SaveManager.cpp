#include "SaveManager.hpp"

void SaveManager::loadSave(fs::path savePath, std::shared_ptr<Scene> scene) {
  // loading the save file
  std::ifstream reader(savePath);
  json save;
  reader >> save;
  reader.close();

  loadPlayer(save["player"], scene);
}

void SaveManager::loadPlayer(json &playerData, std::shared_ptr<Scene> scene) {
  EntityID player = scene->createEntity();
  SaveManager::idMapping["player"] = std::vector<EntityID>{player};

  scene->addComponents(player, std::make_shared<Position>(playerData["position"]), std::make_shared<BodyColor>(playerData["color"]),
                       std::make_shared<Hp>((int)playerData["hp"]), std::make_shared<Size>(playerData["size"]));
}

void SaveManager::updateSave(fs::path savePath, std::shared_ptr<Scene> scene) {
  json save{{"player", savePlayer(scene)}};
  std::cout << save << std::endl;
  std::ofstream file(savePath);  // loading the json object into a file
  file << std::setw(4) << save;
  file.close();
}

json SaveManager::savePlayer(std::shared_ptr<Scene> scene) {
  json playerSave;
  auto components = scene->getEntityComponents(idMapping["player"].at(0));
  for (size_t i = 0; i < MAX_COMPONENTS; i++) {
    bool hasComponent = (*components)[i];
    if (hasComponent) {
      playerSave.update(scene->getComponentSave(idMapping["player"].at(0), i));
    }
  }
  return playerSave;
}
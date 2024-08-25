#include "SaveManager.hpp"

void SaveManager::loadSave(fs::path savePath, std::shared_ptr<Scene> scene) {
  // loading the save file
  std::ifstream reader(savePath);
  json save;
  reader >> save;
  reader.close();

  loadPlayer(save["player"], scene);
  loadEquippedItems(save["equippedItems"], scene);
}

json SaveManager::savePlayer(std::shared_ptr<Scene> scene) {
  json playerSave;
  auto components = scene->getEntityComponents(idMapping["player"]);
  for (size_t i = 0; i < MAX_COMPONENTS; i++) {
    bool hasComponent = (*components)[i];
    if (hasComponent) {
      playerSave.update(scene->getComponentSave(idMapping["player"], i));
    }
  }
  return playerSave;
}

void SaveManager::loadPlayer(json &playerData, std::shared_ptr<Scene> scene) {
  EntityID player = scene->createEntity();
  SaveManager::idMapping["player"] = player;

  scene->addComponents(player, std::make_shared<Position>(playerData["position"]), std::make_shared<BodyColor>(playerData["color"]),
                       std::make_shared<Hp>((int)playerData["hp"]), std::make_shared<Size>(playerData["size"]));
}

void SaveManager::updateSave(fs::path savePath, std::shared_ptr<Scene> scene) {
  json save{{"player", savePlayer(scene)}, {"equippedItems", saveEquippedItems(scene)}};
  std::cout << save << std::endl;
  std::ofstream file(savePath);  // loading the json object into a file
  file << std::setw(4) << save;
  file.close();
}

json SaveManager::saveEquippedItems(std::shared_ptr<Scene> scene) {
  json equippedItemsSave;
  if (idMapping["equippedItems"].contains("helmet")) equippedItemsSave["helmet"] = saveItem(scene, idMapping["equippedItems"]["helmet"]);
  if (idMapping["equippedItems"].contains("armour")) equippedItemsSave["armour"] = saveItem(scene, idMapping["equippedItems"]["armour"]);
  if (idMapping["equippedItems"].contains("weapon")) equippedItemsSave["weapon"] = saveItem(scene, idMapping["equippedItems"]["weapon"]);
  if (idMapping["equippedItems"].contains("pants")) equippedItemsSave["pants"] = saveItem(scene, idMapping["equippedItems"]["pants"]);
  if (idMapping["equippedItems"].contains("boots")) equippedItemsSave["boots"] = saveItem(scene, idMapping["equippedItems"]["boots"]);
  return equippedItemsSave;
}

void SaveManager::loadEquippedItems(json &save, std::shared_ptr<Scene> scene) {
  if (save.contains("helmet")) {
    EntityID helmetID = scene->createEntity();
    idMapping["equippedItems"]["helmet"] = helmetID;
    loadItem(save["helmet"], scene, helmetID);
  }
  if (save.contains("armour")) {
    EntityID armourID = scene->createEntity();
    idMapping["equippedItems"]["armour"] = armourID;
    loadItem(save["armour"], scene, armourID);
  }
  if (save.contains("weapon")) {
    EntityID weaponID = scene->createEntity();
    idMapping["equippedItems"]["weapon"] = weaponID;
    loadItem(save["weapon"], scene, weaponID);
  }
  if (save.contains("pants")) {
    EntityID pantsID = scene->createEntity();
    idMapping["equippedItems"]["pants"] = pantsID;
    loadItem(save["pants"], scene, pantsID);
  }
  if (save.contains("boots")) {
    EntityID bootsID = scene->createEntity();
    idMapping["equippedItems"]["boots"] = bootsID;
    loadItem(save["boots"], scene, bootsID);
  }
}

json SaveManager::saveItem(std::shared_ptr<Scene> scene, EntityID entityID) {
  json j;
  if (scene->entityHasComponent<ItemType>(entityID)) j.update(scene->getComponentSave(entityID, ItemType::id));
  if (scene->entityHasComponent<TextureName>(entityID)) j.update(scene->getComponentSave(entityID, TextureName::id));
  if (scene->entityHasComponent<AttackRange>(entityID)) j.update(scene->getComponentSave(entityID, AttackRange::id));
  if (scene->entityHasComponent<Defense>(entityID)) j.update(scene->getComponentSave(entityID, Defense::id));
  if (scene->entityHasComponent<AttackBonus>(entityID)) j.update(scene->getComponentSave(entityID, AttackBonus::id));
  return j;
}

void SaveManager::loadItem(json &save, std::shared_ptr<Scene> scene, EntityID entityID) {
  if (save.contains("itemType")) {
    scene->addComponent<ItemType>(entityID, std::make_shared<ItemType>(save));
  };
  if (save.contains("textureName")) {
    scene->addComponent<TextureName>(entityID, std::make_shared<TextureName>(save));
  };
  if (save.contains("attackRange")) {
    scene->addComponent<AttackRange>(entityID, std::make_shared<AttackRange>(save));
  };
  if (save.contains("defense")) {
    scene->addComponent<Defense>(entityID, std::make_shared<Defense>(save));
  };
  if (save.contains("attackBonus")) {
    scene->addComponent<AttackBonus>(entityID, std::make_shared<AttackBonus>(save));
  };
}
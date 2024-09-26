#include "UiSystem.hpp"

UiSystem::UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

void UiSystem::handleCharacterScreen(EquippedItems &equippedItems, Inventory &inventory) {
  std::string equippedActions{"equippedActions"};

  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("character", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
  // if the item isn't equipped we draw an empty texture
  std::string helmetTextureName =
      equippedItems.helmet ? scene->getComponent<TextureName>(equippedItems.helmet.value())->textureName : image::other::TRANSPARENT;
  std::string armourTextureName =
      equippedItems.armour ? scene->getComponent<TextureName>(equippedItems.armour.value())->textureName : image::other::TRANSPARENT;
  std::string bootsTextureName = equippedItems.boots ? scene->getComponent<TextureName>(equippedItems.boots.value())->textureName : image::other::TRANSPARENT;
  std::string weaponTextureName =
      equippedItems.weapon ? scene->getComponent<TextureName>(equippedItems.weapon.value())->textureName : image::other::TRANSPARENT;

  static std::optional<EntityID> *eqRef;

  // helmet
  ImVec2 itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.1f, true);
  if (ImGui::ImageButton(_assets->GetTexture(helmetTextureName), ImGuiHelper::toVector2f(itemSize)) && equippedItems.helmet) {
    eqRef = &equippedItems.helmet;
    ImGui::OpenPopup(equippedActions.c_str());
  }
  if (ImGui::IsItemHovered() && equippedItems.helmet) {
    showItemPopup(equippedItems.helmet.value());
  }
  // armour
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.34f, 0.38f, 0.3f);
  if (ImGui::ImageButton(_assets->GetTexture(armourTextureName), ImGuiHelper::toVector2f(itemSize)) && equippedItems.armour) {
    eqRef = &equippedItems.armour;
    ImGui::OpenPopup(equippedActions.c_str());
  }
  if (ImGui::IsItemHovered() && equippedItems.armour) {
    showItemPopup(equippedItems.armour.value());
  }

  // boots
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.7f, true);
  if (ImGui::ImageButton(_assets->GetTexture(bootsTextureName), ImGuiHelper::toVector2f(itemSize)) && equippedItems.boots) {
    eqRef = &equippedItems.boots;
    ImGui::OpenPopup(equippedActions.c_str());
  }
  if (ImGui::IsItemHovered() && equippedItems.boots) {
    showItemPopup(equippedItems.boots.value());
  }

  // weapon
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.07f, 0.4f, true);
  if (ImGui::ImageButton(_assets->GetTexture(weaponTextureName), ImGuiHelper::toVector2f(itemSize)) && equippedItems.weapon) {
    eqRef = &equippedItems.weapon;
    ImGui::OpenPopup(equippedActions.c_str());
  }
  if (ImGui::IsItemHovered() && equippedItems.weapon) {
    showItemPopup(equippedItems.weapon.value());
  }

  if (ImGui::BeginPopup(equippedActions.c_str())) {
    if (ImGui::Button("unequip")) {
      inventory.push_back(eqRef->value());
      eqRef->reset();
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }
  ImGui::End();
}

void UiSystem::handleInventory(std::vector<EntityID> &inventory, EquippedItems &equippedItems) {
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("inventory", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
  const int inventoryWidth = 4;
  const int inventoryHeight = 10;
  size_t eqCounter = 0;

  static int selectedAction = -1;
  const char *actionNames[] = {"Equip", "Delete"};

  std::vector<std::function<void()>> actions;

  // equip action
  actions.push_back([&]() {
    EntityID itemId = inventory.at(eqCounter);
    inventory.erase(inventory.begin() + eqCounter);
    ItemTypes itemType = scene->getComponent<ItemType>(itemId)->itemType;
    switch (itemType) {
      case ItemTypes::HELMET:
        if (equippedItems.helmet) {
          inventory.push_back(equippedItems.helmet.value());
        }
        equippedItems.helmet = itemId;
        break;
      case ItemTypes::ARMOUR:
        if (equippedItems.armour) {
          inventory.push_back(equippedItems.armour.value());
        }
        equippedItems.armour = itemId;
        break;
      case ItemTypes::WEAPON:
        if (equippedItems.weapon) {
          inventory.push_back(equippedItems.weapon.value());
        }
        equippedItems.weapon = itemId;
        break;
      case ItemTypes::PANTS:
        if (equippedItems.pants) {
          inventory.push_back(equippedItems.pants.value());
        }
        equippedItems.pants = itemId;
        break;
      case ItemTypes::BOOTS:
        if (equippedItems.boots) {
          inventory.push_back(equippedItems.boots.value());
        }
        equippedItems.boots = itemId;
        break;
    }
  });

  // delete action
  actions.push_back([&]() {
    scene->removeEntity(inventory.at(eqCounter));
    inventory.erase(inventory.begin() + eqCounter);
  });

  if (ImGui::BeginTable("inventory", inventoryWidth)) {
    for (int row = 0; row < inventoryHeight; row++) {
      ImGui::TableNextRow();
      for (int column = 0; column < inventoryWidth; column++) {
        ImGui::TableSetColumnIndex(column);
        std::string popupName = "popup" + std::to_string(inventoryWidth * row + column);
        ImGui::PushID(inventoryWidth * row + column);
        if (eqCounter < inventory.size()) {
          std::string eqTextureName = scene->getComponent<TextureName>(inventory.at(eqCounter))->textureName;
          if (ImGui::ImageButton(_assets->GetTexture(eqTextureName))) {
            ImGui::OpenPopup(popupName.c_str());
          }
          if (ImGui::IsItemHovered()) {
            showItemPopup(inventory.at(eqCounter));
          }
        } else {
          ImGui::Button("chuj");
        }
        ImGui::SameLine();
        if (ImGui::BeginPopup(popupName.c_str())) {
          for (int i = 0; i < IM_ARRAYSIZE(actionNames); i++) {
            if (ImGui::Button(actionNames[i])) {
              actions.at(i)();
              ImGui::CloseCurrentPopup();
            }
          }
          ImGui::EndPopup();
        }
        ImGui::PopID();
        eqCounter++;
      }
    }
    ImGui::EndTable();
  }
  ImGui::End();
}

void UiSystem::showItemPopup(EntityID id) {
  ImGui::SetNextWindowPos(ImVec2(ImGui::GetMousePos().x - 200.0f, ImGui::GetMousePos().y + 5.0f));
  ImGui::Begin("Debug component list", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
  auto components = scene->getEntityComponents(id);
  for (size_t i = 0; i < MAX_COMPONENTS; i++) {
    bool hasComponent = (*components)[i];
    if (hasComponent) {
      ImGui::Text(scene->getDescription(id, i).c_str());
    }
  }
  ImGui::End();
}

json UiSystem::saveEquippedItems(EquippedItems equippedItems) {
  json equippedItemsSave;
  if (equippedItems.helmet) equippedItemsSave["helmet"] = saveItem(equippedItems.helmet.value());
  if (equippedItems.armour) equippedItemsSave["armour"] = saveItem(equippedItems.armour.value());
  if (equippedItems.weapon) equippedItemsSave["weapon"] = saveItem(equippedItems.weapon.value());
  if (equippedItems.pants) equippedItemsSave["pants"] = saveItem(equippedItems.pants.value());
  if (equippedItems.boots) equippedItemsSave["boots"] = saveItem(equippedItems.boots.value());
  return equippedItemsSave;
}

void UiSystem::loadEquippedItems(json &save, EquippedItems &equippedItems) {
  if (save.contains("helmet")) {
    EntityID helmetID = scene->createEntity();
    equippedItems.helmet = helmetID;
    loadItem(save["helmet"], helmetID);
  }
  if (save.contains("armour")) {
    EntityID armourID = scene->createEntity();
    equippedItems.armour = armourID;
    loadItem(save["armour"], armourID);
  }
  if (save.contains("weapon")) {
    EntityID weaponID = scene->createEntity();
    equippedItems.weapon = weaponID;
    loadItem(save["weapon"], weaponID);
  }
  if (save.contains("pants")) {
    EntityID pantsID = scene->createEntity();
    equippedItems.pants = pantsID;
    loadItem(save["pants"], pantsID);
  }
  if (save.contains("boots")) {
    EntityID bootsID = scene->createEntity();
    equippedItems.boots = bootsID;
    loadItem(save["boots"], bootsID);
  }
}

json UiSystem::saveInventory(Inventory inventory) {
  json save;
  for (auto itemID : inventory) {
    save.push_back(saveItem(itemID));
  }
  return save;
}

void UiSystem::loadInventory(json &j, Inventory &inventory) {
  for (auto &item : j) {
    EntityID itemID = scene->createEntity();
    inventory.push_back(itemID);
    loadItem(item, itemID);
  }
}

json UiSystem::saveItem(EntityID entityID) {
  json j;
  if (scene->entityHasComponent<ItemType>(entityID)) j.update(scene->getComponentSave(entityID, ItemType::id));
  if (scene->entityHasComponent<TextureName>(entityID)) j.update(scene->getComponentSave(entityID, TextureName::id));
  if (scene->entityHasComponent<AttackRange>(entityID)) j.update(scene->getComponentSave(entityID, AttackRange::id));
  if (scene->entityHasComponent<Defense>(entityID)) j.update(scene->getComponentSave(entityID, Defense::id));
  if (scene->entityHasComponent<AttackBonus>(entityID)) j.update(scene->getComponentSave(entityID, AttackBonus::id));
  return j;
}

void UiSystem::loadItem(json &save, EntityID entityID) {
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
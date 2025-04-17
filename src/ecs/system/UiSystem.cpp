#include "UiSystem.hpp"

UiSystem::UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context) {
  std::ifstream reader(fs::current_path().parent_path() / "data" / "textDescriptions" / "UI" / "Traits.json");
  reader >> traitsJson;
  reader.close();
};

void UiSystem::handleCharacterScreen(EquippedItems &equippedItems, Inventory &inventory) {
  std::string equippedActions{"equippedActions"};

  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("character", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

  static std::optional<EntityID> *eqRef;

  std::vector<std::tuple<float, float, float, float, bool>> eqSlotPositions = {
      {0.24f, 0.0f, 0.38f, 0.1f, true}, {0.24f, 0.0f, 0.38f, 0.3f, true}, {0.24f, 0.0f, 0.38f, 0.7f, true}, {0.24f, 0.0f, 0.07f, 0.4f, true}};

  for (size_t slot = 0; slot < eqSlotPositions.size(); slot++) {
    ImVec2 itemSize = std::apply(ImGuiHelper::prepareItem, eqSlotPositions.at(slot));
    if (ImGui::ImageButton(_assets->GetTexture(equippedItems.getTextureName(slot)), ImGuiHelper::toVector2f(itemSize)) && equippedItems.itemVec.at(slot)) {
      eqRef = &equippedItems.itemVec.at(slot);
      ImGui::OpenPopup(equippedActions.c_str());
    }
    if (ImGui::IsItemHovered() && equippedItems.itemVec.at(slot)) {
      showItemPopup(equippedItems.itemVec.at(slot).value());
    }
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
  const char *actionNames[] = {"Equip 1", "Equip 2", "Equip 3", "Equip 4", "Delete"};

  std::vector<std::function<void(int)>> actions;

  // equip action
  auto equipItem = [&](int slot) {
    std::cout << slot << std::endl;
    EntityID itemId = inventory.at(eqCounter);
    inventory.erase(inventory.begin() + eqCounter);

    if (equippedItems.itemVec.at(slot)) {
      inventory.push_back(equippedItems.itemVec.at(slot).value());
    }
    equippedItems.itemVec.at(slot) = itemId;
  };

  // delete action
  auto deleteItem = [&](int slot) {
    scene->removeEntity(inventory.at(eqCounter));
    inventory.erase(inventory.begin() + eqCounter);
  };

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
          ImGui::Button("   ");
        }
        ImGui::SameLine();
        if (ImGui::BeginPopup(popupName.c_str())) {
          for (int i = 0; i < IM_ARRAYSIZE(actionNames); i++) {
            if (ImGui::Button(actionNames[i])) {
              if (i == IM_ARRAYSIZE(actionNames) - 1) {
                deleteItem(i);
              } else {
                equipItem(i);
              }
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

void UiSystem::handleActiveSkillBar(EquippedItems &equippedItems) {
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_MIDDLE, 0.60f, 0.10f);
  ImGui::Begin("skillBar", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

  for (int i = 0; i < SLOT_CAP; i++) {
    ImVec2 itemSize = ImGuiHelper::prepareItem(0.08f, 0.0f, 0.01f + 0.099f * i, 0.1f, true);
    ImGui::ImageButton(_assets->GetTexture(equippedItems.getTextureName(i)), ImGuiHelper::toVector2f(itemSize));
    if (ImGui::IsItemHovered() && i < equippedItems.itemVec.size() && equippedItems.itemVec.at(i)) {
      showItemPopup(equippedItems.itemVec.at(i).value());
    }
  }
  ImGui::End();
}

void UiSystem::showItemPopup(EntityID id) {
  ImGui::SetNextWindowPos(ImVec2(std::max(ImGui::GetMousePos().x - 200.0f, 0.0f), ImGui::GetMousePos().y + 5.0f));
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
  size_t currentSlot = 0;
  for (const auto &item : equippedItems.itemVec) {
    if (item) equippedItemsSave[std::to_string(currentSlot)] = saveItem(item.value());
    currentSlot++;
  }
  return {"equippedItems", equippedItemsSave};
}

void UiSystem::loadEquippedItems(json &save, EquippedItems &equippedItems) {
  for (int i = 0; i < SLOT_CAP; i++) {
    if (save.contains(std::to_string(i))) {
      EntityID itemID = scene->createEntity();
      equippedItems.itemVec.at(i) = itemID;
      loadItem(save[std::to_string(i)], itemID);
    }
  }
}

json UiSystem::saveInventory(Inventory inventory) {
  json save;
  for (auto itemID : inventory) {
    save.push_back(saveItem(itemID));
  }
  return {"inventory", save};
}

void UiSystem::loadInventory(json &j, Inventory &inventory) {
  for (auto &item : j) {
    EntityID itemID = scene->createEntity();
    inventory.push_back(itemID);
    loadItem(item, itemID);
  }
}

// conversion from Traits.json to inventory is very ugly, but better than breaking the serialization conventions
void UiSystem::loadBoughtTraits(json save, Inventory &inventory) {
  for (const auto &boughtTraitNumber : save["boughtTraits"]) {
    int traitIndex = boughtTraitNumber.get<int>();
    auto currentTrait = traitsJson["Traits"].at(traitIndex);
    EntityID traitID = scene->createEntity();
    switch (traitIndex) {
      case 0:
        scene->addComponent<MeleeAttack>(traitID, std::make_shared<MeleeAttack>(currentTrait["stats"]["damage"].get<float>()));
        break;
      case 1:
        scene->addComponent<RangedAttack>(
            traitID, std::make_shared<RangedAttack>(currentTrait["stats"]["range"].get<float>(), currentTrait["stats"]["damage"].get<float>()));
        break;
      default:
        break;
    }
    scene->addComponent<TextureName>(traitID, std::make_shared<TextureName>(currentTrait["textureName"].get<std::string>()));
    inventory.push_back(traitID);
  }
}

json UiSystem::saveItem(EntityID entityID) {
  json j;
  if (scene->entityHasComponent<TextureName>(entityID)) j.update(scene->getComponentSave(entityID, TextureName::id));
  if (scene->entityHasComponent<MeleeAttack>(entityID)) j.update(scene->getComponentSave(entityID, MeleeAttack::id));
  if (scene->entityHasComponent<RangedAttack>(entityID)) j.update(scene->getComponentSave(entityID, RangedAttack::id));
  return j;
}

void UiSystem::loadItem(json &save, EntityID entityID) {
  if (save.contains("textureName")) {
    scene->addComponent<TextureName>(entityID, std::make_shared<TextureName>(save));
  }
  if (save.contains("rangedAttack")) {
    scene->addComponent<RangedAttack>(entityID, std::make_shared<RangedAttack>(save));
    return;
  }
  if (save.contains("meleeAttack")) {
    scene->addComponent<MeleeAttack>(entityID, std::make_shared<MeleeAttack>(save));
    return;
  }
}
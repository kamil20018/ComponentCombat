#include "UiSystem.hpp"

UiSystem::UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

void UiSystem::handleCharacterScreen(EquippedItems equippedItems) {
  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("character", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

  //if the item isn't equipped we draw an empty texture
  std::string helmetTextureName = equippedItems.helmet ? scene->getComponent<TextureName>(equippedItems.helmet.value())->textureName : Item::TRANSPARENT;
  std::string armourTextureName = equippedItems.armour ? scene->getComponent<TextureName>(equippedItems.armour.value())->textureName : Item::TRANSPARENT;
  std::string bootsTextureName = equippedItems.boots ? scene->getComponent<TextureName>(equippedItems.boots.value())->textureName : Item::TRANSPARENT;
  std::string weaponTextureName = equippedItems.weapon ? scene->getComponent<TextureName>(equippedItems.weapon.value())->textureName : Item::TRANSPARENT;

  //helmet
  ImVec2 itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.1f, true);
  ImGui::ImageButton(_assets->GetTexture(helmetTextureName), ImGuiHelper::toVector2f(itemSize));
  if(ImGui::IsItemHovered() && equippedItems.helmet){
    showItemPopup(equippedItems.helmet.value());
  }

  //armour
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.34f, 0.38f, 0.3f);
  ImGui::ImageButton(_assets->GetTexture(armourTextureName), ImGuiHelper::toVector2f(itemSize));
  if(ImGui::IsItemHovered() && equippedItems.armour){
    showItemPopup(equippedItems.armour.value());
  }

  //boots
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.7f, true);
  ImGui::ImageButton(_assets->GetTexture(bootsTextureName), ImGuiHelper::toVector2f(itemSize));
  if(ImGui::IsItemHovered() && equippedItems.boots){
    showItemPopup(equippedItems.boots.value());
  }

  //weapon
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.07f, 0.4f, true);
  ImGui::ImageButton(_assets->GetTexture(weaponTextureName), ImGuiHelper::toVector2f(itemSize));
  if(ImGui::IsItemHovered() && equippedItems.weapon){
    showItemPopup(equippedItems.weapon.value());
  }
  ImGui::End();
}

void UiSystem::handleInventory(std::vector<EntityID> &inventory, EquippedItems &equippedItems) {
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("inventory", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
  const int inventoryWidth = 4;
  const int inventoryHeight = 10;
  int eqCounter = 0;

  static int selectedAction = -1;
  const char *actionNames[] = {"Equip", "Delete"};
  
  std::vector<std::function<void()>> actions;
  
  //equip action
  actions.push_back([&]() {
    EntityID itemId = inventory.at(eqCounter);
    inventory.erase(inventory.begin() + eqCounter); 
    ItemTypes itemType = scene->getComponent<ItemType>(itemId)->type;
    switch(itemType){
      case ItemTypes::HELMET:
        if(equippedItems.helmet){
          inventory.push_back(equippedItems.helmet.value());
        }
        equippedItems.helmet = itemId;
        break;
      case ItemTypes::ARMOUR:
        if(equippedItems.armour){
          inventory.push_back(equippedItems.armour.value());
        }
        equippedItems.armour = itemId;
        break;
      case ItemTypes::WEAPON:
        if(equippedItems.weapon){
          inventory.push_back(equippedItems.weapon.value());
        }
        equippedItems.weapon = itemId;
        break;
      case ItemTypes::PANTS:
        if(equippedItems.pants){
          inventory.push_back(equippedItems.pants.value());
        }
        equippedItems.pants = itemId;
        break;
      case ItemTypes::BOOTS:
        if(equippedItems.boots){
          inventory.push_back(equippedItems.boots.value());
        }
        equippedItems.boots = itemId;
        break;
    }
  });

  //delete action
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
        if(eqCounter < inventory.size()){
          std::string eqTextureName = scene->getComponent<TextureName>(inventory.at(eqCounter))->textureName;
          if (ImGui::ImageButton(_assets->GetTexture(eqTextureName))) {
            ImGui::OpenPopup(popupName.c_str());
          }
          if(ImGui::IsItemHovered()){
            showItemPopup(inventory.at(eqCounter));
          }
        } else {
          ImGui::Button("chuj");
        }
          ImGui::SameLine();
        if (ImGui::BeginPopup(popupName.c_str())) {
          for (int i = 0; i < IM_ARRAYSIZE(actionNames); i++){
            if(ImGui::Button(actionNames[i])){
              actions.at(i)();
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

void UiSystem::showItemPopup(EntityID id){
  ImGui::SetNextWindowPos(ImVec2(ImGui::GetMousePos().x - 200.0f, ImGui::GetMousePos().y + 5.0f));
  ImGui::Begin("Debug component list", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
  auto components = scene->getEntityComponents(id);
  for (size_t i = 0; i < MAX_COMPONENTS; i++) {
    bool hasComponent = (*components)[i];
    if (hasComponent) {
      ImGui::Text(scene->getDescription(id, i).c_str());
    }
  }
  ImGui::End();
}
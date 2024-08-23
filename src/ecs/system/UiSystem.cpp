#include "UiSystem.hpp"

UiSystem::UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

void UiSystem::handleCharacterScreen(EquippedItems equippedItems) {
  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("character", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

  const sf::Texture &defaultTransparent = _assets->GetTexture(Item::TRANSPARENT); 

  //helmet
  ImVec2 itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.1f, true);
  ImGui::ImageButton(defaultTransparent, ImGuiHelper::toVector2f(itemSize));

  //armour
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.34f, 0.38f, 0.3f);
  ImGui::ImageButton(defaultTransparent, ImGuiHelper::toVector2f(itemSize));

  //shoes
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.7f, true);
  ImGui::ImageButton(defaultTransparent, ImGuiHelper::toVector2f(itemSize));

  //weapon
  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.07f, 0.4f, true);
  ImGui::ImageButton(defaultTransparent, ImGuiHelper::toVector2f(itemSize));
  ImGui::End();
}

void UiSystem::handleInventory(const std::vector<EntityID> &inventory) {
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("inventory", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
  const int inventoryWidth = 4;
  const int inventoryHeight = 10;
  // variables below are placeholders for the proper equipment functionality
  [[maybe_unused]] static int selected_fish = -1;
  [[maybe_unused]] const char *names[] = {"Bream", "Haddock", "Mackerel", "Pollock", "Tilefish"};
  [[maybe_unused]] static bool toggles[] = {true, false, false, false, false};

  int eqCounter = 0;

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
          eqCounter++;
        } else {
          ImGui::Button("chuj");
        }
          ImGui::SameLine();
        if (ImGui::BeginPopup(popupName.c_str())) {
          ImGui::Text(popupName.c_str());
          ImGui::Separator();
          for (int i = 0; i < IM_ARRAYSIZE(names); i++)
            if (ImGui::Selectable(names[i])) selected_fish = i;
          ImGui::EndPopup();
        }
        ImGui::PopID();
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

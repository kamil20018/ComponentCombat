#include "UiSystem.hpp"

UiSystem::UiSystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

void UiSystem::handleCharacterScreen() {
  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("character", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
  ImVec2 itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.1f, true);
  ImGui::Button("head", itemSize);

  itemSize = ImGuiHelper::prepareItem(0.24f, 0.34f, 0.38f, 0.3f);
  ImGui::Button("body", itemSize);

  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.38f, 0.7f, true);
  ImGui::Button("legs", itemSize);

  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.07f, 0.4f, true);
  ImGui::Button("left_arm", itemSize);

  itemSize = ImGuiHelper::prepareItem(0.24f, 0.0f, 0.69f, 0.4f, true);
  ImGui::Button("right_arm", itemSize);
  ImGui::End();
}

void UiSystem::handleInventory() {
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("inventory", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
  const int inventoryWidth = 4;
  const int inventoryHeight = 10;
  // variables below are placeholders for the proper equipment functionality
  [[maybe_unused]] static int selected_fish = -1;
  [[maybe_unused]] const char *names[] = {"Bream", "Haddock", "Mackerel", "Pollock", "Tilefish"};
  [[maybe_unused]] static bool toggles[] = {true, false, false, false, false};
  if (ImGui::BeginTable("inventory", inventoryWidth)) {
    for (int row = 0; row < inventoryHeight; row++) {
      ImGui::TableNextRow();
      for (int column = 0; column < inventoryWidth; column++) {
        ImGui::TableSetColumnIndex(column);
        std::string popupName = "popup" + std::to_string(inventoryWidth * row + column);
        ImGui::PushID(inventoryWidth * row + column);
        if (ImGui::ImageButton(_assets->GetTexture("book"))) {
          ImGui::OpenPopup(popupName.c_str());
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

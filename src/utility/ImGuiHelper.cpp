#include "ImGuiHelper.hpp"

void ImGuiHelper::dockNextWindow(WindowDock dockDir, float widthPercent, float heightPercent, float xPadding, float yPadding) {
  ImGuiIO &io = ImGui::GetIO();
  float screenWidth = io.DisplaySize.x;
  float screenHeight = io.DisplaySize.y;

  xPadding *= screenWidth;
  yPadding *= screenHeight;

  float windowWidth = screenWidth * widthPercent;
  float windowHeight = screenHeight * heightPercent;
  ImGui::SetNextWindowSize(ImVec2(screenWidth * widthPercent, screenHeight * heightPercent));
  switch (dockDir) {
    case WindowDock::TOP_LEFT:
      ImGui::SetNextWindowPos(ImVec2(xPadding, yPadding));
      break;
    case WindowDock::TOP_RIGHT:
      ImGui::SetNextWindowPos(ImVec2(screenWidth - windowWidth - xPadding, yPadding));
      break;
    case WindowDock::BOTTOM_LEFT:
      ImGui::SetNextWindowPos(ImVec2(xPadding, screenHeight - windowHeight - yPadding));
      break;
    case WindowDock::BOTTOM_RIGHT:
      ImGui::SetNextWindowPos(ImVec2(screenWidth - windowWidth - xPadding, screenHeight - windowHeight - yPadding));
      break;
    case WindowDock::TOP_MIDDLE:
      ImGui::SetNextWindowPos(ImVec2((screenWidth - windowWidth) / 2.0f, yPadding));
      break;
    case WindowDock::RIGHT_MIDDLE:
      ImGui::SetNextWindowPos(ImVec2(screenWidth - windowWidth - xPadding, (screenHeight - windowHeight) / 2.0f));
      break;
    case WindowDock::BOTTOM_MIDDLE:
      ImGui::SetNextWindowPos(ImVec2((screenWidth - windowWidth) / 2.0f, screenHeight - windowHeight - yPadding));
      break;
    case WindowDock::LEFT_MIDDLE:
      ImGui::SetNextWindowPos(ImVec2(xPadding, (screenHeight - windowHeight) / 2.0f));
      break;
    case WindowDock::CENTER:
      ImGui::SetNextWindowPos(ImVec2((screenWidth - windowWidth) / 2.0f, (screenHeight - windowHeight) / 2.0f));
      break;
  }
}

ImVec2 ImGuiHelper::prepareItem(float widthPercent, float heightPercent, float xPosPercent, float yPosPercent, bool square) {
  ImVec2 windowSize = ImGui::GetWindowSize();
  ImVec2 elementSize;

  ImGui::SetCursorPos(ImVec2(windowSize.x * xPosPercent, windowSize.y * yPosPercent));

  elementSize.x = windowSize.x * widthPercent;
  if (square) {
    elementSize.y = elementSize.x;
  } else {
    elementSize.y = windowSize.y * heightPercent;
  }

  return elementSize;
}

sf::Vector2f ImGuiHelper::toVector2f(ImVec2 vec) {
  return sf::Vector2f(vec.x, vec.y);
}
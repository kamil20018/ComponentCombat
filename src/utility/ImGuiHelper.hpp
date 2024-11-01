#pragma once

#include <imgui-SFML.h>
#include <imgui.h>

#include <functional>
enum class WindowDock { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_MIDDLE, RIGHT_MIDDLE, BOTTOM_MIDDLE, LEFT_MIDDLE, CENTER };

class ImGuiHelper {
 public:
  /// @brief Sets the size and docks the window, padding is relative to the docking direction!
  static void dockNextWindow(WindowDock dockDir, float widthPercent, float heightPercent, float xPadding = 0.0f, float yPadding = 0.0f);
  /// @brief Positions the elements in the main window in a more general way than dockNextWindow -
  /// @brief only takes into account the top left corner of the window when positioning
  /// @param square ignores the heightPercent forcing the item to be a square
  /// @return size for the item
  static ImVec2 prepareItem(float widthPercent, float heightPercent, float xPosPercent, float yPosPercent, bool square = false);
  /// @brief For easier sfml integration
  static sf::Vector2f toVector2f(ImVec2 vec);
};

namespace MyGui {
  inline void centerHorizontally(float width) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - width) * 0.5f);
  }

  inline void verticalPaddingAbsolute(float height) {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
  }

  inline void topDownPaddingAbsolute(float height, std::function<void()> guiElementRenderer) {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
    guiElementRenderer();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + height);
  }

  inline void verticalPaddingRelative(float percentage) {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetWindowSize().y * percentage);
  }

  inline void topDownPaddingRelative(float percentage, std::function<void()> guiElementRenderer) {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetWindowSize().y * percentage);
    guiElementRenderer();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetWindowSize().y * percentage);
  }

  inline void TextWrapped(std::string text) {
    ImGui::TextWrapped(text.c_str());
  }

  inline void BulletText(std::string text) {
    ImGui::BulletText(text.c_str());
  }
}  // namespace MyGui

#pragma once

#include <imgui-SFML.h>
#include <imgui.h>

enum class WindowDock { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_MIDDLE, RIGHT_MIDDLE, BOTTOM_MIDDLE, LEFT_MIDDLE, CENTER };

class ImGuiHelper {
 public:
  static void dockNextWindow(WindowDock dockDir, float widthPercent, float heightPercent, float xPadding = 0.0f, float yPadding = 0.0f);
};

#include "UiTest.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

UiTest::UiTest(std::shared_ptr<Context> &context) : context(context) {}

UiTest::~UiTest() {}

void UiTest::init() { ImGui::SFML::Init(*_window); }

void UiTest::processInput() {
  sf::Event event;

  while (context->window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      context->window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {  // captures user keyboard input, may be useful
                                 // in the future
        case sf::Keyboard::Escape:
          _window->close();
          break;
        default: {
          break;
        }
      }
    }
  }
}

void UiTest::update() {
  ImGui::SFML::Update(*_window, deltaClock.restart());
  ImGuiIO &io = ImGui::GetIO();
}

void UiTest::draw() {
  _window->clear();
  handleWindow();
  ImGui::ShowDemoWindow();
  ImGui::SFML::Render(*_window);
  _window->display();
}

void UiTest::handleWindow() {
  bool *open;
  ImVec2 saveButtonSize(200.f, 50.f);
  ImGuiHelper::dockNextWindow(WindowDock::CENTER, 0.5f, 0.5f);
  ImGui::Begin("test", open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
  const int inventoryWidth = 12;
  const int inventoryHeight = 6;
  static int selected_fish = -1;
  const char *names[] = {"Bream", "Haddock", "Mackerel", "Pollock", "Tilefish"};
  static bool toggles[] = {true, false, false, false, false};
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

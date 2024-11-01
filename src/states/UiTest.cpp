#include "UiTest.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

UiTest::UiTest(std::shared_ptr<Context> &context) : context(context) {}

UiTest::~UiTest() {}

void UiTest::init() {
  ImGui::SFML::Init(*_window);
}

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
  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.2f, 0.5f, 0.05f, 0.05f);
  ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
  ImGui::BeginTable("table2", 3, ImGuiTableFlags_SizingStretchSame, ImGui::GetContentRegionAvail());
  ImGui::TableSetupColumn("a");
  ImGui::TableSetupColumn("b");
  ImGui::TableHeadersRow();

  for (int i = 0; i < 7; i++) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("a %d", i);
    ImGui::TableNextRow();
    ImGui::Text("b %d", i);
    ImGui::TableNextColumn();
    ImGui::Text("c %d", i);
  }
  ImGui::EndTable();
  ImGui::End();
}

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
  ImGui::SFML::Render(*_window);
  _window->display();
}

void UiTest::handleWindow() {
  bool *open;
  ImVec2 saveButtonSize(200.f, 50.f);
  ImGuiHelper::dockNextWindow(WindowDock::LEFT_MIDDLE, 0.5f, 0.5f, 0.05f,
                              0.15f);
  ImGui::Begin("test", open,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
  ImGui::End();
}

#include "UiTest.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

UiTest::UiTest(std::shared_ptr<Context> &context) : context(context) {
  ShaderManager::init();
}

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
  ImGui::ShowDemoWindow();
  sf::RectangleShape rectangle(sf::Vector2f(40, 40));
  rectangle.setFillColor(sf::Color::Magenta);
  rectangle.setPosition(200, 200);
  // rectangle.setTextureRect(sf::IntRect(0, 0, 40, 40));
  ShaderManager::shaders[ShaderType::CURRENT_SKILL_AREA].setUniform("u_resolution", sf::Glsl::Vec2{40, 40});
  ShaderManager::shaders[ShaderType::CURRENT_SKILL_AREA].setUniform("u_time", shaderClock.getElapsedTime().asSeconds());

  _window->draw(rectangle, &ShaderManager::shaders[ShaderType::CURRENT_SKILL_AREA]);

  ImGui::SFML::Render(*_window);
  _window->display();
}

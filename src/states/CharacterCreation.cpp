#include "CharacterCreation.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <filesystem>
#include <fstream>

CharacterCreation::CharacterCreation(std::shared_ptr<Context> &context) : context(context) {}

CharacterCreation::~CharacterCreation() {}

void CharacterCreation::init() {
  ImGui::SFML::Init(*_window);
}

void CharacterCreation::processInput() {
  sf::Event event;

  while (context->window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      context->window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        default: {
          break;
        }
      }
    }
  }
}

void CharacterCreation::update() {
  std::cout << "character creation" << std::endl;
  _states->addState(std::make_unique<GamePlay>(context));
}

void CharacterCreation::draw() {
  _window->clear(sf::Color::Black);
  ImGui::ShowDemoWindow();
  ImGui::SFML::Render(*_window);
  _window->display();
}

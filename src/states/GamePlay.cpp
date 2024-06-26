#include "GamePlay.h"

GamePlay::GamePlay(std::shared_ptr<Context> context)
    : context(context), scene(std::make_shared<Scene>()), system(scene) {
  ImGui::SFML::Init(*_window);

  // for (int i = 0; i < 5; i++) {
  //   EntityID dog = scene->createEntity();

  //   auto position = std::make_shared<component::Position>(i, i);
  //   auto size = std::make_shared<component::Size>(TILE_SIZE, TILE_SIZE);
  //   auto hp = std::make_shared<component::Hp>(100);
  //   auto color = std::make_shared<component::BodyColor>(sf::Color::Red);

  //   (scene->addComponent(dog, size)).addComponent(dog, hp).addComponent(dog,
  //   color).addComponent(dog, position);
  // }
}

void GamePlay::init() {}

void GamePlay::processInput() {
  sf::Event event;
  while (_window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      _window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::Escape:
          _window->close();
          break;
      }
    }
  }
}

void GamePlay::update() { ImGui::SFML::Update(*_window, deltaClock.restart()); }

void GamePlay::draw() {
  _window->clear();
  system.drawEntities(_window);
  system.drawComponents(sf::Mouse::getPosition(*_window));
  ImGui::SFML::Render(*_window);
  _window->display();
}

void GamePlay::componentSelection() {}
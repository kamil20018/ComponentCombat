#include <SFML/Graphics/CircleShape.hpp>

#include "Simulation.h"

Game::Game() : context(std::make_shared<Context>()) {
  _window->create(sf::VideoMode(1200, 800), "Simulation", sf::Style::Close);
  _window->setFramerateLimit(60);
  _window->setPosition(sf::Vector2i(200, 200));

  _states->addState(std::make_unique<Simulation>(this->context));
}

Game::~Game() {}

void Game::run() {
  while (_window->isOpen()) {
    _states->processStateChange();
    _states->getCurrent()->processInput();
    _states->getCurrent()->update();
    _states->getCurrent()->draw();
  }
}
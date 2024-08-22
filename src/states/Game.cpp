#include <SFML/Graphics/CircleShape.hpp>

#include "LoadGame.h"
#include "MainMenu.h"
#include "UiTest.hpp"
Game::Game() : context(std::make_shared<Context>()) {
  _window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulation", sf::Style::Close);
  _window->setFramerateLimit(60);
  _window->setPosition(sf::Vector2i(200, 200));
  imageLoader::load(context);
  // _states->addState(std::make_unique<MainMenu>(this->context));
  _states->addState(std::make_unique<LoadGame>(this->context));
  // _states->addState(std::make_unique<GamePlay>(this->context));
  // _states->addState(std::make_unique<UiTest>(this->context));
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
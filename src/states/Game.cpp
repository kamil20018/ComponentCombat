#include <SFML/Graphics/CircleShape.hpp>

#include "LoadGame.hpp"
#include "MainMenu.hpp"
#include "Timer.hpp"
#include "UiTest.hpp"
Game::Game() : context(std::make_shared<Context>()) {
  _window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulation", sf::Style::Close);
  _window->setFramerateLimit(60);
  _window->setPosition(sf::Vector2i(200, 200));
  imageLoader::loadAllItems(context);
  // _states->addState(std::make_unique<MainMenu>(this->context)); // go to first state, skipped for easier testing
  _states->addState(std::make_unique<LoadGame>(this->context));  // go to testing state
  // _states->addState(std::make_unique<UiTest>(this->context)); // strictly for ui experiments
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
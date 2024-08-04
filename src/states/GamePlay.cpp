#include "GamePlay.h"

GamePlay::GamePlay(std::shared_ptr<Context> context)
    : context(context), scene(std::make_shared<Scene>()), system(scene) {
  ImGui::SFML::Init(*_window);

  player = scene->createEntity();

  scene->addComponents(player, 
    std::make_shared<component::Position>(sf::Vector2i(14, 13)),
    std::make_shared<component::BodyColor>(sf::Color::Red),
    std::make_shared<component::Size>(TILE_SIZE, TILE_SIZE),
    std::make_shared<component::Hp>(100)
  );

  auto savePath = context->savePath; //useless now, important to load this in the future
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
        case sf::Keyboard::W:
          moveDir = sf::Vector2i(0, -1);
          break;
        case sf::Keyboard::S:
          moveDir = sf::Vector2i(0, 1);
          break;
        case sf::Keyboard::A:
          moveDir = sf::Vector2i(-1, 0);
          break;
        case sf::Keyboard::D:
          moveDir = sf::Vector2i(1, 0);
          break;
        case sf::Keyboard::Escape:
          _window->close();
          break;
      }
    }
  }
}

void GamePlay::update() { 
  ImGui::SFML::Update(*_window, deltaClock.restart()); 
  system.moveEntity(1, moveDir);
  moveDir = sf::Vector2i(0, 0);
}

void GamePlay::draw() {
  _window->clear();

  drawDebugLines();

  system.drawEntities(_window);
  system.drawComponents(sf::Mouse::getPosition(*_window));
  ImGui::SFML::Render(*_window);

  sf::RectangleShape line(sf::Vector2f(150, 5));
  _window->display();
}

void GamePlay::drawDebugLines(){
  const int thickness = 2;
  
  for(int i = 0; i < WINDOW_WIDTH; i+= TILE_SIZE){
    sf::RectangleShape line(sf::Vector2f(thickness, WINDOW_HEIGHT));
    line.setPosition(sf::Vector2f(i, 0));
    line.setFillColor(sf::Color::Red);
    _window->draw(line);
  }
  for(int i = 0; i < WINDOW_HEIGHT; i+= TILE_SIZE){
    sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH, thickness));
    line.setPosition(sf::Vector2f(0, i));
    line.setFillColor(sf::Color::Red);
    _window->draw(line);
  }
}

void GamePlay::componentSelection() {}
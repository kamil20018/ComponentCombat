#include "TraitActivator.hpp"

TraitActivator::TraitActivator(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context, std::shared_ptr<sf::RenderWindow> window)
    : scene(scene), context(context), window(window) {}

void TraitActivator::showMeeleAttack(EntityID player, sf::Vector2i mouseTilePos) {
  sf::Vector2i playerPos = scene->getComponent<Position>(player)->pos;

  const float PI = 3.14159;
  float mouseAngle = atan2(mouseTilePos.y - playerPos.y, mouseTilePos.x - playerPos.x) * 360.0 / (2 * PI);
  if (mouseAngle < 0) {
    mouseAngle += 360;
  }

  // converting the angle to a direction
  sf::Vector2i direction(0, 0);
  if (mouseAngle < 22.5f || mouseAngle > 337.5f) {
    direction = sf::Vector2i(1, 0);
  } else if (mouseAngle > 22.5f && mouseAngle < 67.5f) {
    direction = sf::Vector2i(1, 1);
  } else if (mouseAngle > 67.5f && mouseAngle < 112.5f) {
    direction = sf::Vector2i(0, 1);
  } else if (mouseAngle > 112.5f && mouseAngle < 157.5f) {
    direction = sf::Vector2i(-1, 1);
  } else if (mouseAngle > 157.5f && mouseAngle < 202.5f) {
    direction = sf::Vector2i(-1, 0);
  } else if (mouseAngle > 202.5f && mouseAngle < 247.5f) {
    direction = sf::Vector2i(-1, -1);
  } else if (mouseAngle > 247.5f && mouseAngle < 292.5f) {
    direction = sf::Vector2i(0, -1);
  } else if (mouseAngle > 292.5f && mouseAngle < 337.5f) {
    direction = sf::Vector2i(1, -1);
  }

  sf::Vector2i position = playerPos + direction;
  sf::RectangleShape rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
  rectangle.setFillColor(sf::Color::Magenta);
  rectangle.setPosition(position.x * TILE_SIZE, position.y * TILE_SIZE);
  // window->draw(rectangle);
  std::cout << "traitActivator " << position.x << " " << position.y << std::endl;
  activeShaders[position] = ShaderType::CURRENT_SKILL_AREA;
}

void TraitActivator::showRangedDefault(EntityID player, sf::Vector2i mouseTilePos, int range) {
  sf::Vector2i playerPos = scene->getComponent<Position>(player)->pos;

  if (sqrt(pow(playerPos.x - mouseTilePos.x, 2) + pow(playerPos.y - mouseTilePos.y, 2)) < range) {
    sf::RectangleShape rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(mouseTilePos.x * TILE_SIZE, mouseTilePos.y * TILE_SIZE);
    window->draw(rectangle);
  }
}
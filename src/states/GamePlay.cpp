#include "GamePlay.hpp"

GamePlay::GamePlay(std::shared_ptr<Context> context) : context(context), scene(std::make_shared<Scene>()), system(scene), uiSystem(scene, context) {
  ImGui::SFML::Init(*_window);
  auto savePath = context->savePath;
  mockCreateInventory();
}

void GamePlay::init() {
  std::ifstream reader(context->savePath);
  json save;
  reader >> save;
  reader.close();
  loadPlayer(save["player"]);
  uiSystem.loadEquippedItems(save["equippedItems"], equippedItems);
}

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
          context->states->popCurrent();
          // _window->close();
          break;
        default:
          break;
      }
    }
  }
}

void GamePlay::update() {
  ImGui::SFML::Update(*_window, deltaClock.restart());
  system.moveEntity(player, moveDir);
  moveDir = sf::Vector2i(0, 0);
  handleSaveButton();
  uiSystem.handleInventory(inventory, equippedItems);
  uiSystem.handleCharacterScreen(equippedItems);
}

void GamePlay::draw() {
  _window->clear();

  drawDebugLines();
  system.drawEntities(_window);
  system.drawComponents(sf::Mouse::getPosition(*_window));

  ImGui::ShowDemoWindow();
  ImGui::SFML::Render(*_window);

  _window->display();
}

void GamePlay::drawDebugLines() {
  const int thickness = 2;

  for (int i = 0; i < WINDOW_WIDTH; i += TILE_SIZE) {
    sf::RectangleShape line(sf::Vector2f(thickness, WINDOW_HEIGHT));
    line.setPosition(sf::Vector2f(i, 0));
    line.setFillColor(sf::Color(100, 100, 100));
    _window->draw(line);
  }
  for (int i = 0; i < WINDOW_HEIGHT; i += TILE_SIZE) {
    sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH, thickness));
    line.setPosition(sf::Vector2f(0, i));
    line.setFillColor(sf::Color(100, 100, 100));
    _window->draw(line);
  }
}

void GamePlay::handleSaveButton() {
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_LEFT, 0.1f, 0.1f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("saveButton", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

  float buttonHue = 0.67f;
  ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(buttonHue, 0.6f, 0.6f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(buttonHue, 0.7f, 0.7f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(buttonHue, 0.8f, 0.8f));
  if (ImGui::Button("Save", ImGui::GetContentRegionAvail())) {
    updateSave();
  }
  ImGui::PopStyleColor(3);
  ImGui::End();
  ImGui::PopStyleVar();
}

void GamePlay::mockCreateInventory() {
  inventory.push_back(scene->createEntity());
  scene->addComponents(inventory.at(0), std::make_shared<ItemType>(ItemTypes::WEAPON),
                       std::make_shared<TextureName>((std::string)image::items::weapon::GREATSWORD1), std::make_shared<AttackRange>(5.0f, 10.0f));

  inventory.push_back(scene->createEntity());
  scene->addComponents(inventory.at(1), std::make_shared<ItemType>(ItemTypes::WEAPON), std::make_shared<TextureName>((std::string)image::items::weapon::DAGGER),
                       std::make_shared<AttackRange>(15.0f, 20.0f));

  inventory.push_back(scene->createEntity());
  scene->addComponents(inventory.at(2), std::make_shared<ItemType>(ItemTypes::WEAPON), std::make_shared<TextureName>((std::string)image::items::weapon::CLUB),
                       std::make_shared<AttackRange>(25.0f, 30.0f));
  inventory.push_back(scene->createEntity());
  scene->addComponents(inventory.at(3), std::make_shared<ItemType>(ItemTypes::ARMOUR), std::make_shared<TextureName>((std::string)image::items::armour::CLOAK2),
                       std::make_shared<Defense>(5.0f), std::make_shared<AttackBonus>(5.0f));
  // equippedItems.weapon = scene->createEntity();
  // scene->addComponents(equippedItems.weapon.value(), std::make_shared<ItemType>(ItemTypes::WEAPON),
  //                      std::make_shared<TextureName>((std::string)image::items::weapon::GREATSWORD2), std::make_shared<AttackRange>(5.0f, 10.0f));
}

json GamePlay::savePlayer() {
  json playerSave;
  auto components = scene->getEntityComponents(player);
  for (size_t i = 0; i < MAX_COMPONENTS; i++) {
    bool hasComponent = (*components)[i];
    if (hasComponent) {
      playerSave.update(scene->getComponentSave(player, i));
    }
  }
  return playerSave;
}

void GamePlay::loadPlayer(json &playerData) {
  player = scene->createEntity();
  scene->addComponents(player, std::make_shared<Position>(playerData["position"]), std::make_shared<BodyColor>(playerData["color"]),
                       std::make_shared<Hp>((int)playerData["hp"]), std::make_shared<Size>(playerData["size"]));
}

void GamePlay::updateSave() {
    json save {
      {"equippedItems", uiSystem.saveEquippedItems(equippedItems)},
      {"player", savePlayer()}
    };
    std::cout << save << std::setw(4) << std::endl;
    std::ofstream file(context->savePath);  // loading the json object into a file
    file << std::setw(4) << save;
    file.close();
}

#include "GamePlay.hpp"

GamePlay::GamePlay(std::shared_ptr<Context> context) : context(context), scene(std::make_shared<Scene>()), system(scene), uiSystem(scene, context) {
  ImGui::SFML::Init(*_window);
  auto savePath = context->savePath;
  // mockCreateInventory();
}

void GamePlay::init() {
  std::ifstream reader(context->savePath);
  json save;
  reader >> save;
  reader.close();
  loadPlayer(save["player"]);
  uiSystem.loadEquippedItems(save["equippedItems"], equippedItems);
  uiSystem.loadInventory(save["inventory"], inventory);

  enemy = scene->createEntity();
  scene->addComponents(enemy, std::make_shared<BodyColor>(sf::Color::Blue), std::make_shared<Position>(sf::Vector2i(2, 2)), std::make_shared<Size>(40, 40),
                       std::make_shared<Sight>(14), std::make_shared<Range>(7),std::make_shared<Attack>(7));

  BT::BehaviorTreeFactory factory;
  factory.registerSimpleCondition("InSight", [&](BT::TreeNode &) {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    auto sight = scene->getComponent<Sight>(enemy);
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < sight->sight ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  });
  factory.registerSimpleCondition("InRange", [&](BT::TreeNode &) {
    auto playerPos = scene->getComponent<Position>(player);
    auto enemyPos = scene->getComponent<Position>(enemy);
    auto range = scene->getComponent<Range>(enemy);
    float distance = sqrt(pow(playerPos->pos.x - enemyPos->pos.x, 2) + pow(playerPos->pos.y - enemyPos->pos.y, 2));
    return distance < range->range ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
  });
  factory.registerSimpleCondition("AttackPlayer", [&](BT::TreeNode &) {
    auto enemyAttack = scene->getComponent<Attack>(enemy)->attack;
    auto playerHp = &scene->getComponent<Hp>(player)->hp;
    *playerHp -= enemyAttack;
    std::cout << "-----NEXT ATTACK-----" << std::endl;
    std::cout << "player hp: " << scene->getComponent<Hp>(player)->hp << std::endl;
    std::cout << "player was hit with " << enemyAttack << " damage" << std::endl;
    std::cout << "player has " << *playerHp << " hp left" << std::endl;
    return BT::NodeStatus::SUCCESS;
  });
  factory.registerSimpleCondition("ApproachPlayer",
                                  [&](BT::TreeNode &) {
                                    auto playerPos = &scene->getComponent<Position>(player)->pos;
                                    auto enemyPos = &scene->getComponent<Position>(enemy)->pos;
                                    auto distance = sf::Vector2i(playerPos->x - enemyPos->x, playerPos->y - enemyPos->y);
                                    bool hor = abs(distance.x) > abs(distance.y);
                                    if (hor) {
                                      if (distance.x > 0) {
                                        *enemyPos += sf::Vector2i(1, 0);
                                      } else if (distance.x < 0) {
                                        *enemyPos += sf::Vector2i(-1, 0);
                                      }
                                    } else {
                                      if (distance.y > 0) {
                                        *enemyPos += sf::Vector2i(0, 1);
                                      } else if (distance.y < 0) {
                                        *enemyPos += sf::Vector2i(0, -1);
                                      }
                                    }

                                    return BT::NodeStatus::SUCCESS;
                                  }

  );
  // factory.registerNodeType<ApproachObject>("ApproachObject", scene, player);
  // factory.registerNodeType<OpenSth>("OpenSth");
  tree = factory.createTreeFromFile(fs::current_path().parent_path() / "resources" / "behavior_trees" / "my_tree.xml");
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
  if (moveDir != sf::Vector2i(0, 0)) tree.tickExactlyOnce();
  moveDir = sf::Vector2i(0, 0);
  handleSaveButton();
  uiSystem.handleInventory(inventory, equippedItems);
  uiSystem.handleCharacterScreen(equippedItems, inventory);
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
  json save{{"equippedItems", uiSystem.saveEquippedItems(equippedItems)}, {"inventory", uiSystem.saveInventory(inventory)}, {"player", savePlayer()}};
  std::ofstream file(context->savePath);  // loading the json object into a file
  file << std::setw(4) << save;
  file.close();
}

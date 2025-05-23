#include "GamePlay.hpp"

GamePlay::GamePlay(std::shared_ptr<Context> context, bool newGame)
    : context(context),
      scene(std::make_shared<Scene>()),
      system(scene),
      uiSystem(scene, context),
      traitActivator(scene, context, _window),
      playerUsedAction(false),
      equippedItems(scene),
      newGame(newGame) {
  ImGui::SFML::Init(*_window);
  effectSystem = std::make_shared<EffectSystem>(scene);
  enemySystem = EnemySystem(scene, effectSystem, context);
  auto savePath = context->savePath;
  std::ofstream file(context->savePath);  // loading the json object into a file
  file << std::setw(4) << context->saveFile;
  file.close();
}

void GamePlay::init() {
  json gameStateSave = context->saveFile["gameState"];
  loadPlayer(gameStateSave["player"]);
  if (newGame) {
    uiSystem.loadBoughtTraits(context->saveFile["metaProgression"], inventory);
  }
  uiSystem.loadEquippedItems(gameStateSave["equippedItems"], equippedItems);
  uiSystem.loadInventory(gameStateSave["inventory"], inventory);
  enemySystem.loadEnemies(gameStateSave["enemies"]);
  enemySystem.spawn(0);
}

void GamePlay::processInput() {
  sf::Event event;
  while (_window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      _window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        // movement
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
        case sf::Keyboard::Space:
          passTurn = true;
          break;
        // leave game
        case sf::Keyboard::Escape:
          context->states->popCurrent();
          break;
        case sf::Keyboard::I:
          inventoryOpen = !inventoryOpen;
          break;
        case sf::Keyboard::L:
          logOpened = !logOpened;
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
  if (moveDir != sf::Vector2i(0, 0) || passTurn) {
    passTurn = false;
    effectSystem->resetAppliedThisTurn();
    enemySystem.enemyTurn();
  };
  effectSystem->updateEffectStatuses();
  moveDir = sf::Vector2i(0, 0);
  handleSaveButton();
}

void GamePlay::draw() {
  _window->clear();

  if (inventoryOpen) {
    uiSystem.handleInventory(inventory, equippedItems);
    uiSystem.handleCharacterScreen(equippedItems, inventory);
  }

  uiSystem.handleActiveSkillBar(equippedItems);

  drawDebugLines();
  system.drawEntities(_window);
  system.drawComponents(getMouseTilePosition());
  traitActivator.drawActiveSkill(uiSystem.getSelectedSkill(), player, getMouseTilePosition());

  if (logOpened) {
    CombatLog::display();
  }

  ImGui::ShowDemoWindow();

  ImGui::SFML::Render(*_window);

  _window->display();
}

sf::Vector2i GamePlay::getMouseTilePosition() {
  sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
  return sf::Vector2i(mousePos.x / TILE_SIZE, mousePos.y / TILE_SIZE);
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
  scene->addComponents(inventory.at(0), std::make_shared<RangedAttack>(10, 2),
                       std::make_shared<TextureName>((std::string)image::spells::conjuration::MAGIC_DART));

  inventory.push_back(scene->createEntity());
  scene->addComponents(inventory.at(1), std::make_shared<MeleeAttack>(5), std::make_shared<TextureName>((std::string)image::items::weapon::CLUB));
}

json GamePlay::savePlayer() {
  return {"player", scene->getEntitySave(player)};
}

json GamePlay::saveMetaProgression() {
  return {"metaProgression", context->saveFile["metaProgression"]};
}

json GamePlay::saveStateDestination() {
  return {"stateDestination", "gamePlay"};
}

void GamePlay::loadPlayer(json &playerData) {
  player = scene->createEntity();
  enemySystem.setPlayer(player);
  scene->addComponents(player, std::make_shared<Position>(playerData), std::make_shared<BodyColor>(playerData), std::make_shared<Hp>(playerData),
                       std::make_shared<Size>(playerData));
}

void GamePlay::updateSave() {
  json save{{"gameState", {uiSystem.saveEquippedItems(equippedItems), uiSystem.saveInventory(inventory), savePlayer(), enemySystem.saveEnemies()}},
            saveMetaProgression(),
            saveStateDestination()};
  std::ofstream file(context->savePath);  // loading the json object into a file
  file << std::setw(4) << save;
  file.close();
}

#include "GamePlay.h"

GamePlay::GamePlay(std::shared_ptr<Context> context) : context(context), scene(std::make_shared<Scene>()), system(scene) {
  ImGui::SFML::Init(*_window);
  auto savePath = context->savePath;
  SaveManager::loadSave(savePath, scene);
  player = SaveManager::idMapping.at("player").at(0);
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
          context->states->popCurrent();
          // _window->close();
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
  handleInventory();
  handleCharacterScreen();
  ImGui::ShowDemoWindow();
}

void GamePlay::draw() {
  _window->clear();

  drawDebugLines();
  system.drawEntities(_window);
  system.drawComponents(sf::Mouse::getPosition(*_window));
  ImGui::SFML::Render(*_window);

  _window->display();
}

void GamePlay::drawDebugLines() {
  const int thickness = 2;

  for (int i = 0; i < WINDOW_WIDTH; i += TILE_SIZE) {
    sf::RectangleShape line(sf::Vector2f(thickness, WINDOW_HEIGHT));
    line.setPosition(sf::Vector2f(i, 0));
    line.setFillColor(sf::Color(100,100,100));
    _window->draw(line);
  }
  for (int i = 0; i < WINDOW_HEIGHT; i += TILE_SIZE) {
    sf::RectangleShape line(sf::Vector2f(WINDOW_WIDTH, thickness));
    line.setPosition(sf::Vector2f(0, i));
    line.setFillColor(sf::Color(100,100,100));
    _window->draw(line);
  }
}

void GamePlay::handleSaveButton() {
  bool *open;

  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_LEFT, 0.1f, 0.1f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("saveButton", open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

  float buttonHue = 0.67f;
  ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(buttonHue, 0.6f, 0.6f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(buttonHue, 0.7f, 0.7f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(buttonHue, 0.8f, 0.8f));
  if (ImGui::Button("Save", ImGui::GetContentRegionAvail())) {
    SaveManager::updateSave(context->savePath, scene);
  }
  ImGui::PopStyleColor(3);
  ImGui::End();
  ImGui::PopStyleVar();
}

void GamePlay::handleInventory() {
  bool *open;
  ImGuiHelper::dockNextWindow(WindowDock::BOTTOM_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("inventory", open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
  const int inventoryWidth = 4;
  const int inventoryHeight = 10;
  static int selected_fish = -1;
  const char *names[] = {"Bream", "Haddock", "Mackerel", "Pollock", "Tilefish"};
  static bool toggles[] = {true, false, false, false, false};
  if (ImGui::BeginTable("inventory", inventoryWidth)) {
    for (int row = 0; row < inventoryHeight; row++) {
      ImGui::TableNextRow();
      for (int column = 0; column < inventoryWidth; column++) {
        ImGui::TableSetColumnIndex(column);
        std::string popupName = "popup" + std::to_string(inventoryWidth * row + column);
        ImGui::PushID(inventoryWidth * row + column);
        if (ImGui::ImageButton(_assets->GetTexture("book"))) {
          ImGui::OpenPopup(popupName.c_str());
        }
        ImGui::SameLine();
        if (ImGui::BeginPopup(popupName.c_str())) {
          ImGui::Text(popupName.c_str());
          ImGui::Separator();
          for (int i = 0; i < IM_ARRAYSIZE(names); i++)
            if (ImGui::Selectable(names[i])) selected_fish = i;
          ImGui::EndPopup();
        }
        ImGui::PopID();
      }
    }
    ImGui::EndTable();
  }
  ImGui::End();
}

void GamePlay::handleCharacterScreen() {
  bool *open;
  ImGuiHelper::dockNextWindow(WindowDock::TOP_RIGHT, 0.19f, 0.49f, 0.005f, 0.005f);
  ImGui::Begin("character", open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
  ImGui::End();
}
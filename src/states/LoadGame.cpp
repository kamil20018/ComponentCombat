#include "LoadGame.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <filesystem>
#include <fstream>

LoadGame::LoadGame(std::shared_ptr<Context> &context)
    : context(context),
      baseSavePath(fs::current_path().parent_path() / "data" / "saves" / "base.json"),
      userSavesPath(fs::current_path().parent_path() / "data" / "userSaves"),
      pressedEnter(false),
      pressedEscape(false),
      arrowInput(0),
      selectedSaveIndex(0) {
  updateSaveFiles();
}

LoadGame::~LoadGame() {}

void LoadGame::init() {
  ImGui::SFML::Init(*_window);
}

void LoadGame::processInput() {
  sf::Event event;

  while (context->window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      context->window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::Escape:
          pressedEscape = true;
          break;
        case sf::Keyboard::Enter:
          pressedEnter = true;
          break;
        case sf::Keyboard::Up:
          arrowInput = -1;
          break;
        case sf::Keyboard::Down:
          arrowInput = 1;
          break;
        default: {
          break;
        }
      }
    }
  }
}

void LoadGame::update() {
  bool load = false;
  switch (arrowInput) {
    case -1:
      if (selectedSaveIndex == 0)
        selectedSaveIndex = saveFiles.size() - 1;
      else
        selectedSaveIndex--;
      break;
    case 1:
      ++selectedSaveIndex %= saveFiles.size();
    default:
      break;
  }
  arrowInput = 0;
  ImGui::SFML::Update(*_window, deltaClock.restart());
  bool *open = NULL;
  ImGuiIO &io = ImGui::GetIO();
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.7, io.DisplaySize.y * 0.7));
  ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
  ImGui::Begin("Choose an exisiting save file, or create a new one", open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
  for (size_t n = 0; n < saveFiles.size(); n++) {
    std::string text = saveFiles.at(n).stem();
    if (ImGui::Selectable(text.c_str(), selectedSaveIndex == n)) selectedSaveIndex = n;
  }

  if (ImGui::Button("Load")) {
    load = true;
  }
  ImGui::SameLine();
  if (ImGui::Button("Create a new save file")) {
    ImGui::OpenPopup("New Save");
  }
  handleCreateSavePopup();
  ImGui::SameLine();
  if (ImGui::Button("Delete")) {
    ImGui::OpenPopup("Delete");
  }
  handleDeletePopup();

  ImGui::End();
  if (load || pressedEnter) {
    context->savePath = saveFiles.at(selectedSaveIndex);
    std::ifstream reader(context->savePath);
    reader >> context->saveFile;
    reader.close();
    auto destination = context->saveFile["stateDestination"];
    if (destination == "gamePlay") {
      _states->addState(std::make_unique<GamePlay>(context));
    } else if (destination == "characterCreation") {
      _states->addState(std::make_unique<CharacterCreation>(context));
    }
  }
  pressedEnter = false;
  pressedEscape = false;
}

void LoadGame::draw() {
  _window->clear(sf::Color::Black);
  ImGui::ShowDemoWindow();
  ImGui::SFML::Render(*_window);
  _window->display();
}

void LoadGame::handleCreateSavePopup() {
  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  static char saveName[16];
  if (ImGui::BeginPopupModal("New Save", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::InputText("Save Name", saveName, IM_ARRAYSIZE(saveName));
    if (ImGui::Button("OK", ImVec2(120, 0)) || pressedEnter) {
      pressedEnter = false;
      context->savePath = createSaveFile(saveName);
      updateSaveFiles();
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0)) || pressedEscape) {
      pressedEscape = false;
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}

void LoadGame::handleDeletePopup() {
  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
  if (ImGui::BeginPopupModal("Delete", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
    if (ImGui::Button("OK", ImVec2(120, 0))) {
      deleteSave(saveFiles.at(selectedSaveIndex).stem().string());
      updateSaveFiles();
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}

void LoadGame::updateSaveFiles() {
  if (!fs::exists(userSavesPath)) {
    std::cout << "ERROR: path to the save files doesn't exit" << std::endl;
    std::exit(1);
  }
  saveFiles.clear();
  for (auto const &dir_entry : fs::directory_iterator{userSavesPath}) saveFiles.push_back(dir_entry.path());
}

fs::path LoadGame::createSaveFile(const std::string &saveName) {
  fs::path inputPath = baseSavePath;
  fs::path outputPath = userSavesPath / (saveName + ".json");
  std::cout << baseSavePath << " " << userSavesPath << " " << saveName << std::endl;
  std::ifstream inputFile(inputPath);
  std::ofstream outputFile(outputPath);
  if (inputFile.is_open() && outputFile.is_open()) {
    std::string line;

    while (std::getline(inputFile, line)) {
      outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::cout << "File copied successfully." << std::endl;
  } else {
    std::cout << "Failed to open the files." << std::endl;
  }

  return outputPath;
}

void LoadGame::deleteSave(const std::string &saveName) {
  fs::path path = userSavesPath / (saveName + ".json");
  fs::remove(path);
}
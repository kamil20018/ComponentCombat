#include "LoadGame.h"

#include <imgui-SFML.h>
#include <imgui.h>

#include <filesystem>
#include <fstream>

LoadGame::LoadGame(std::shared_ptr<Context> &context) : context(context) { updateSaveFiles(); }

LoadGame::~LoadGame() {}

void LoadGame::init() { ImGui::SFML::Init(*_window); }

void LoadGame::processInput() {
  sf::Event event;

  while (context->window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      context->window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        default: {
          break;
        }
      }
    }
  }
}

void LoadGame::update() {
  bool load = false;

  ImGui::SFML::Update(*_window, deltaClock.restart());
  bool *open = NULL;
  ImGuiIO &io = ImGui::GetIO();
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.7, io.DisplaySize.y * 0.7));
  ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always,
                          ImVec2(0.5f, 0.5f));
  ImGui::Begin("Choose an exisiting save file, or create a new one", open,
               ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
  static int selected = -1;
  for (int n = 0; n < saveFiles.size(); n++) {
    std::string text = "Save " + std::to_string(n);
    if (ImGui::Selectable(text.c_str(), selected == n)) selected = n;
  }

  if (ImGui::Button("Create a new save file")) {
    context->savePath = createSaveFile();
    updateSaveFiles();
  }

  ImGui::SameLine();
  if (ImGui::Button("Load") && selected != -1) {
    load = true;
    context->savePath = saveFiles.at(selected);
  }

  ImGui::End();
  if (load) _states->addState(std::make_unique<Simulation>(context));
}

void LoadGame::draw() {
  _window->clear(sf::Color::Black);

  ImGui::SFML::Render(*_window);
  _window->display();
}

void LoadGame::updateSaveFiles() {
  fs::path path = fs::current_path().parent_path() / "data" / "saves";
  if (!fs::exists(path)) {
    std::cout << "ERROR: path to the save files doesn't exit" << std::endl;
    std::exit(1);
  }
  saveFiles.clear();
  for (auto const &dir_entry : fs::directory_iterator{path}) saveFiles.push_back(dir_entry.path());
}

fs::path LoadGame::createSaveFile() {
  fs::path path =
      fs::current_path().parent_path() / "data" / "saves" / ("new " + std::to_string(saveFiles.size() + 2) + ".json");
  std::ofstream ofs(path);
  ofs.close();
  return path;
}
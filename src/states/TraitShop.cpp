#include "TraitShop.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <filesystem>
#include <fstream>

TraitShop::TraitShop(std::shared_ptr<Context> &context) : context(context) {
  ImGui::SFML::Init(*_window);
  std::ifstream reader(fs::current_path().parent_path() / "data" / "textDescriptions" / "UI" / "Traits.json");
  reader >> traitsJson;
  reader.close();
}

TraitShop::~TraitShop() {}

void TraitShop::init() {}

void TraitShop::processInput() {
  sf::Event event;

  while (context->window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      _window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
        case sf::Keyboard::Escape:
          context->states->popCurrent();
          break;
        case sf::Keyboard::Enter:
          context->saveFile["stateDestination"] = "gamePlayNew";
          _states->addState(std::make_unique<GamePlay>(context, true), true);
          break;
        default: {
          break;
        }
      }
    }
  }
}

void TraitShop::update() {
  ImGui::SFML::Update(*_window, deltaClock.restart());
  ImGuiHelper::dockNextWindow(WindowDock::CENTER, 0.75f, 0.75f);
  ImGui::Begin("Character Creation", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse);
  traitShop();
  ImGui::End();
}

void TraitShop::draw() {
  _window->clear(sf::Color::Black);
  sf::Sprite backgroundSprite(_assets->GetTexture(image::backgrounds::OUTPUT));
  float width = _window->getSize().x;
  float height = _window->getSize().y;
  backgroundSprite.setScale(width / backgroundSprite.getGlobalBounds().width, height / backgroundSprite.getGlobalBounds().height);
  _window->draw(backgroundSprite);
  ImGui::ShowDemoWindow();
  ImGui::SFML::Render(*_window);
  _window->display();
}

void TraitShop::traitShop() {
  auto metaProgresstionData = context->saveFile["metaProgression"];
  static ImGuiTableFlags flags1 =
      ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_SizingFixedFit;
  float width = ImGui::GetContentRegionAvail().x * 0.95f;
  ImGui::Text("You have %d evolution points", metaProgresstionData["evolutionPoints"].get<int>());
  MyGui::centerHorizontally(width);
  if (ImGui::BeginTable("table2", 6, flags1, ImVec2(width, 0))) {
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));
    ImGui::TableSetupColumn("Cost");
    ImGui::TableSetupColumn("Name");
    ImGui::TableSetupColumn("Type");
    ImGui::TableSetupColumn("Description");
    ImGui::TableSetupColumn("Details");
    ImGui::TableSetupColumn("Buy");
    ImGui::TableHeadersRow();

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    for (auto trait : traitsJson["Traits"]) {
      ImGui::Text(std::to_string(trait["cost"].get<int>()).c_str());
      ImGui::TableNextColumn();
      ImGui::Text(trait["name"].get<std::string>().c_str());
      ImGui::TableNextColumn();
      ImGui::Text(trait["type"].get<std::string>().c_str());
      ImGui::TableNextColumn();
      ImGui::Text(trait["description"].get<std::string>().c_str());
      ImGui::TableNextColumn();
      ImGui::Text("i");
      ImGui::TableNextColumn();
      ImGui::PushID(trait["number"].get<int>());
      if (ImGui::Button("Buy")) {
        if (trait["cost"].get<int>() <= metaProgresstionData["evolutionPoints"].get<int>()) {
          context->saveFile["metaProgression"]["evolutionPoints"] =
              context->saveFile["metaProgression"]["evolutionPoints"].get<int>() - trait["cost"].get<int>();
          context->saveFile["metaProgression"]["boughtTraits"].push_back(trait["number"]);
        }
      }
      ImGui::PopID();
      ImGui::TableNextRow();
      ImGui::TableNextColumn();
    }

    ImGui::EndTable();
  }

  if (ImGui::Button("Finish")) {
    context->saveFile["stateDestination"] = "gamePlayNew";
    _states->addState(std::make_unique<GamePlay>(context, true));
  }
}

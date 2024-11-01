#include "CharacterCreation.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <filesystem>
#include <fstream>

CharacterCreation::CharacterCreation(std::shared_ptr<Context> &context) : context(context) {
  ImGui::SFML::Init(*_window);
  std::ifstream reader(fs::current_path().parent_path() / "data" / "textDescriptions" / "UI" / "CharacterCreation.json");
  reader >> UiText;
  reader.close();
}

CharacterCreation::~CharacterCreation() {}

void CharacterCreation::init() {}

void CharacterCreation::processInput() {
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
        default: {
          break;
        }
      }
    }
  }
}

void CharacterCreation::update() {
  ImGui::SFML::Update(*_window, deltaClock.restart());
  ImGuiHelper::dockNextWindow(WindowDock::CENTER, 0.75f, 0.75f);
  ImGui::Begin("Character Creation", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse);
  cultivationTypeChoice();
  ImGui::End();
  //_states->addState(std::make_unique<GamePlay>(context));
}

void CharacterCreation::draw() {
  _window->clear(sf::Color::Black);
  ImGui::ShowDemoWindow();
  ImGui::SFML::Render(*_window);
  _window->display();
}

void CharacterCreation::cultivationTypeChoice() {
  static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
  if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_SizingStretchSame | flags1, ImGui::GetContentRegionAvail())) {
    auto showCultivationImage = [&](CultivationType cultivationType) {
      json cultivation = UiText[CultivationTypeToName.at(cultivationType)];
      float size = ImGui::GetContentRegionAvail().x * 0.6f;
      MyGui::centerHorizontally(size);
      MyGui::topDownPaddingRelative(0.05f, [&] {
        ImGui::Image(_assets->GetTexture(cultivationTypeToImageNames.at(cultivationType)), ImVec2(size, size));
      });
    };
    auto showCultivationText = [&](CultivationType cultivationType) {
      json cultivation = UiText[CultivationTypeToName.at(cultivationType)];
      MyGui::topDownPaddingRelative(0.01f, [&] {
        MyGui::TextWrapped(cultivation["description"]);
        ImGui::Text("Pros:");
        for (const auto &pros : cultivation["pros"]) {
          MyGui::TextWrapped(pros);
        }
        ImGui::Text("Cons:");
        for (const auto &cons : cultivation["cons"]) {
          MyGui::TextWrapped(cons);
        }
      });
    };

    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));
    ImGui::TableSetupColumn(CultivationTypeToName.at(CultivationType::QI).c_str());
    ImGui::TableSetupColumn(CultivationTypeToName.at(CultivationType::BODY).c_str());
    ImGui::TableSetupColumn(CultivationTypeToName.at(CultivationType::DEMONIC).c_str());
    ImGui::TableHeadersRow();

    std::vector<CultivationType> cultivationTypes = {CultivationType::QI, CultivationType::BODY, CultivationType::DEMONIC};

    ImGui::TableNextRow();
    for (const auto &cultivationType : cultivationTypes) {
      ImGui::TableNextColumn();
      showCultivationImage(cultivationType);
    }
    ImGui::TableNextRow();
    for (const auto &cultivationType : cultivationTypes) {
      ImGui::TableNextColumn();
      showCultivationText(cultivationType);
    }
    ImGui::EndTable();
  }
}

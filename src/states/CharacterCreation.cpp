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
        case sf::Keyboard::Num1:
          selectedCultivationType = CultivationType::QI;
          break;
        case sf::Keyboard::Num2:
          selectedCultivationType = std::nullopt;
          // selectedCultivationType = CultivationType::BODY;
          break;
        case sf::Keyboard::Num3:
          selectedCultivationType = std::nullopt;
          // selectedCultivationType = CultivationType::DEMONIC;
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
  // if (!selectedCultivationType) {
  //   cultivationTypeChoice();
  // } else {
  cultivatorCreator();
  // }
  ImGui::End();
}

void CharacterCreation::draw() {
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

    auto showCultivationOverview = [&](CultivationType cultivationType) {
      json cultivation = UiText[CultivationTypeToName.at(cultivationType)];
      MyGui::topDownPaddingRelative(0.02f, [&] {
        MyGui::TextWrapped(cultivation["description"]);
      });
    };

    auto showCultivationText = [&](CultivationType cultivationType) {
      json cultivation = UiText[CultivationTypeToName.at(cultivationType)];
      MyGui::topDownPaddingRelative(0.01f, [&] {
        // MyGui::TextWrapped(cultivation["description"]);
        ImGui::Text("Pros:");
        for (const auto &pros : cultivation["pros"]) {
          MyGui::TextWrapped(pros);
        }
        ImGui::Text("Cons:");
        for (const auto &cons : cultivation["cons"]) {
          MyGui::TextWrapped(cons);
        }
      });
      float buttonSize = ImGui::GetContentRegionAvail().x * 0.75f;
      MyGui::centerHorizontally(buttonSize);
      ImGui::SetCursorPosY(ImGui::GetWindowSize().y * 0.93);
      if (cultivationType == CultivationType::QI) {
        if (ImGui::Button("Select", ImVec2(buttonSize, 0))) {
          selectedCultivationType = cultivationType;
        }
      } else {
        if (ImGui::Button("Not Implemented", ImVec2(buttonSize, 0))) {
          // selectedCultivationType = cultivationType;
          std::cout << "not implemented" << std::endl;
        }
      }
    };

    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));
    ImGui::TableSetupColumn(CultivationTypeToName.at(CultivationType::QI).c_str());
    ImGui::TableSetupColumn(CultivationTypeToName.at(CultivationType::BODY).c_str());
    ImGui::TableSetupColumn(CultivationTypeToName.at(CultivationType::DEMONIC).c_str());
    ImGui::TableHeadersRow();

    std::vector<CultivationType> cultivationTypes = {CultivationType::QI, CultivationType::BODY, CultivationType::DEMONIC};

    // images
    ImGui::TableNextRow();
    for (const auto &cultivationType : cultivationTypes) {
      ImGui::TableNextColumn();
      showCultivationImage(cultivationType);
    }
    // overviews
    ImGui::TableNextRow();
    for (const auto &cultivationType : cultivationTypes) {
      ImGui::TableNextColumn();
      showCultivationOverview(cultivationType);
    }
    // descriptions
    ImGui::TableNextRow();
    for (const auto &cultivationType : cultivationTypes) {
      ImGui::TableNextColumn();
      showCultivationText(cultivationType);
    }
    ImGui::EndTable();
  }
}

void CharacterCreation::cultivatorCreator() {
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
    for (auto trait : UiText["Traits"]) {
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
        std::cout << trait["number"] << std::endl;
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
  switch (*selectedCultivationType) {
    case CultivationType::QI:
      qiCultivatorCreator();
      break;
    case CultivationType::BODY:
      bodyCultivatorCreator();
      break;
    case CultivationType::DEMONIC:
      demonicCultivatorCreator();
      break;
  }

  if (ImGui::Button("Finish")) {
    context->saveFile["stateDestination"] = "gamePlay";
    _states->addState(std::make_unique<GamePlay>(context), true);
  }
}

void CharacterCreation::qiCultivatorCreator() {}

void CharacterCreation::bodyCultivatorCreator() {
  // TODO
}

void CharacterCreation::demonicCultivatorCreator() {
  // TODO
}

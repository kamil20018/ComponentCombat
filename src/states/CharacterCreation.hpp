#pragma once

#include <SFML/Graphics/Text.hpp>
#include <filesystem>
#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <vector>

#include "Game.hpp"
#include "GamePlay.hpp"
#include "ImGuiHelper.hpp"
#include "ImageNames.hpp"
#include "State.hpp"
namespace fs = std::filesystem;
using json = nlohmann::json;

enum class CultivationType { QI, BODY, DEMONIC };
inline const std::unordered_map<CultivationType, std::string> CultivationTypeToName{
    {CultivationType::QI, "Qi cultivation"}, {CultivationType::BODY, "Body cultivation"}, {CultivationType::DEMONIC, "Demonic cultivation"}};

inline const std::unordered_map<CultivationType, std::string> cultivationTypeToImageNames{{CultivationType::QI, image::monsters::unique::LOUISE},
                                                                                          {CultivationType::BODY, image::monsters::TITAN},
                                                                                          {CultivationType::DEMONIC, image::monsters::demons::HELLION}};

class CharacterCreation : public State {
 public:
  CharacterCreation(std::shared_ptr<Context>& context);
  ~CharacterCreation();

  void init() override;
  void processInput() override;
  void update() override;
  void draw() override;

 private:
  void cultivationTypeChoice();
  void cultivatorCreator();  // for generic layout, to be filled by selected type
  void qiCultivatorCreator();
  void bodyCultivatorCreator();
  void demonicCultivatorCreator();

  void spendEvolutionPoints(int amount);

  json UiText;
  std::optional<CultivationType> selectedCultivationType;
  std::shared_ptr<Context> context;
  sf::Clock deltaClock;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <unordered_map>
namespace fs = std::filesystem;

enum class ShaderType { POTENTIAL_SKILL_AREA, CURRENT_SKILL_AREA, TEST_BACKGROUND };

class ShaderManager {
 public:
  ShaderManager();
  static void init();
  static void update();
  inline static std::unordered_map<ShaderType, sf::Shader> shaders = [] {
    std::unordered_map<ShaderType, sf::Shader> shaders;
    return shaders;
  }();
  inline static sf::Clock shaderClock = [] {
    sf::Clock shaderClock;
    return shaderClock;
  }();

 private:
};
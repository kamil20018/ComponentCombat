#include "ShaderManager.hpp"

ShaderManager::ShaderManager() {}

void ShaderManager::init() {
  fs::path path = fs::current_path().parent_path() / "shaders" / "backgrounds" / "stars.frag";
  std::cout << fs::is_directory(path) << std::endl;
  std::cout << fs::current_path().parent_path() / "shaders" / "backgrounds" << std::endl;
  shaders[ShaderType::TEST_BACKGROUND];
  shaders.at(ShaderType::TEST_BACKGROUND).loadFromFile(path, sf::Shader::Fragment);
  fs::path path2 = fs::current_path().parent_path() / "shaders" / "attackFields" / "singleTarget.frag";
  shaders[ShaderType::CURRENT_SKILL_AREA];
  shaders.at(ShaderType::CURRENT_SKILL_AREA).loadFromFile(path2, sf::Shader::Fragment);
}

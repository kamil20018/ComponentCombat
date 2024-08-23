#include "AssetManager.hpp"

AssetManager::AssetManager() {}

AssetManager::~AssetManager() {}

void AssetManager::AddTexture(std::string name, const fs::path &filePath, bool wantRepeated) {
  auto texture = std::make_unique<sf::Texture>();
  if (texture->loadFromFile(filePath)) {
    texture->setRepeated(wantRepeated);
    this->textures[name] = std::move(texture);
  }
}

void AssetManager::AddTexture(std::string name, std::unique_ptr<sf::Texture> texture) {
  this->textures[name] = std::move(texture);
}

void AssetManager::AddFont(std::string name, const std::string &filePath) {
  auto font = std::make_unique<sf::Font>();

  if (font->loadFromFile(filePath)) {
    this->fonts[name] = std::move(font);
  }
}

const sf::Texture &AssetManager::GetTexture(std::string name) const {
  return *(this->textures.at(name).get());
}

const sf::Font &AssetManager::GetFont(std::string name) const {
  return *(this->fonts.at(name).get());
}

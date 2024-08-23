#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>

namespace fs = std::filesystem;

class AssetManager {
 private:
  std::map<std::string, int> ints;
  std::map<std::string, std::unique_ptr<sf::Texture>> textures;
  std::map<std::string, std::unique_ptr<sf::Font>> fonts;

 public:
  int abc;
  AssetManager();
  ~AssetManager();

  void AddTexture(std::string name, const fs::path &filePath, bool wantRepeated = false);
  void AddTexture(std::string name, std::unique_ptr<sf::Texture> texture);

  void AddFont(std::string name, const std::string &filePath);

  const sf::Texture &GetTexture(std::string name) const;
  const sf::Font &GetFont(std::string name) const;
};
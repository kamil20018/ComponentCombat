#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Context.hpp"

namespace fs = std::filesystem;

namespace imageLoader {
  namespace {
    fs::path imagePath = fs::current_path().parent_path() / "resources" / "images";
    fs::path itemPath = imagePath / "items";
  }  // namespace

  /// @brief Loads all of the item images with "filename.png" as their key. To access them from the context use Image::FILENAME from ImageNames.hpp
  inline void loadAllItems(std::shared_ptr<Context> context) {
    for (auto const &dir_entry : fs::recursive_directory_iterator{imagePath}) {
      if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".png") {
        _assets->AddTexture(dir_entry.path().filename(), dir_entry.path());
      }
    }
  }
}  // namespace imageLoader

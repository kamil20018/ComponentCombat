#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Context.h"

namespace fs = std::filesystem;

namespace imageLoader {
namespace {
fs::path imagePath = fs::current_path().parent_path() / "resources" / "images";
fs::path itemPath = imagePath / "items";
}  // namespace

inline void loadAllItems(std::shared_ptr<Context> context){
    for (auto const &dir_entry : fs::recursive_directory_iterator{imagePath}){
        if(dir_entry.is_regular_file()){
            std::cout << dir_entry << std::endl;
            _assets->AddTexture(dir_entry.path().filename(), dir_entry.path());
        }
    }
}
}  // namespace imageLoader
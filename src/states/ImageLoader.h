#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "Context.h"

namespace fs = std::filesystem;

namespace imageLoader {
namespace {
fs::path imagePath = fs::current_path().parent_path() / "resources" / "images";
fs::path booksPath = imagePath / "items" / "books";
fs::path foodPath = imagePath / "items" / "food";
}  // namespace

inline void load(std::shared_ptr<Context> context) { context->assets->AddTexture("book", booksPath / "dark_brown.png"); };
}  // namespace imageLoader
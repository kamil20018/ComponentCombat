#pragma once

#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include "Scene.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

class SaveManager {
public:
    static void loadSave(fs::path savePath, std::shared_ptr<Scene> scene);
    static void updateSave(fs::path savePath, std::shared_ptr<Scene> scene);
    inline static std::unordered_map<std::string, std::vector<EntityID>> idMapping;
private:
    static void loadPlayer(json &save, std::shared_ptr<Scene> scene);
    static json savePlayer(std::shared_ptr<Scene> scene);
};

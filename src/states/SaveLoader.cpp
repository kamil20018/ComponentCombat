#include "SaveLoader.hpp"

void SaveLoader::loadSave(fs::path savePath, std::shared_ptr<Scene> scene){
    //loading the save file
    std::ifstream reader(savePath);
    json save;
    reader >> save;
    reader.close();

    loadPlayer(save["player"], scene);
}

void SaveLoader::loadPlayer(json &playerData, std::shared_ptr<Scene> scene){
    EntityID player = scene->createEntity();
    SaveLoader::idMapping["player"] = std::vector<EntityID>{player};

    scene->addComponents(player,
        std::make_shared<Position>(playerData["Position"]),
        std::make_shared<BodyColor>(playerData["Color"]),
        std::make_shared<Hp>((int)playerData["Hp"]),
        std::make_shared<Size>(playerData["Size"])
    );
}
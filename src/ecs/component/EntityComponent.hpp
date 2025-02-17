#pragma once

#include "component/Component.hpp"

namespace component {
  struct Collidable : public Component {
    Collidable(){};
    json serialize() override {
      return json{{"Collidable", true}};
    }
    std::string getDescription() override {
      return "COLLIDABLE";
    }
  };

  struct TextureName : public Component {
    TextureName(std::string textureName) : textureName(textureName){};
    TextureName(const json &j) : textureName(j["textureName"]){};
    json serialize() override {
      return json{{"textureName", textureName}};
    }
    std::string getDescription() override {
      return (std::stringstream() << "ItemTexture | " << textureName).str();
    }
    inline static int id = -1;
    inline static std::string componentName = "TextureName";
    std::string textureName;
  };

}  // namespace component
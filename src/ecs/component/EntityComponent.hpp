#pragma once

#include "component/Component.hpp"

namespace component {   
    struct Collidable : public Component {
        Collidable() {};
        json serialize() override {
            return json{{"Collidable", true}};
        }
        std::string getDescription() override {
            return "COLLIDABLE";
        }
    };
}
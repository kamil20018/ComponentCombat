#pragma once

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
using json = nlohmann::json;

namespace component {
  struct Component {
    Component(){};
    virtual std::string getDescription() {
      return "this component has no description";
    };
    virtual json serialize() = 0;
    inline static int componentCount = 0;
  };
}  // namespace component
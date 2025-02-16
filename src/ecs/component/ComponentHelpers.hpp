#pragma once

#include <array>
#include <string>
#include <unordered_map>

enum class BtType { RANGED, MELEE, COUNT };

inline std::array<std::string, static_cast<int>(BtType::COUNT)> BtTypeToString{"RANGED", "MELEE"};

inline std::unordered_map<std::string, BtType> StringToBtType{{"RANGED", BtType::RANGED}, {"MELEE", BtType::MELEE}};
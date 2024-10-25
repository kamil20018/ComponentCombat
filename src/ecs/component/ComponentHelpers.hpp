#pragma once

#include <array>
#include <string>
#include <unordered_map>

enum class BtType { LONG_RANGE, SHORT_RANGE, COUNT };

inline std::array<std::string, static_cast<int>(BtType::COUNT)> BtTypeToString{"LONG_RANGE", "SHORT_RANGE"};

inline std::unordered_map<std::string, BtType> StringToBtType{{"LONG_RANGE", BtType::LONG_RANGE}, {"SHORT_RANGE", BtType::SHORT_RANGE}};
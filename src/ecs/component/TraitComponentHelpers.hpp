#pragma once

#include <string>
#include <unordered_map>

enum class RangeType { MELEE_NEIGHBOURING, RANGED_DEFAULT };

const std::unordered_map<RangeType, std::string> rangeTypeToString{{RangeType::MELEE_NEIGHBOURING, "meleeNeighbouring"},
                                                                   {RangeType::RANGED_DEFAULT, "rangedDefault"}};

const std::unordered_map<std::string, RangeType> stringToRangeType{{"meleeNeighbouring", RangeType::MELEE_NEIGHBOURING},
                                                                   {"rangedDefault", RangeType::RANGED_DEFAULT}};
add_library(utility "")

target_link_libraries(utility
  PUBLIC
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML
)

target_sources(utility
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/ImGuiHelper.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ImGuiHelper.hpp
  )

target_include_directories(utility
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
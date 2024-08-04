add_library(states "")

target_link_libraries(states
  PUBLIC
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML
    stateManager
    ecs
)

target_sources(states
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadGame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MainMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GamePlay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SaveLoader.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Game.h
    ${CMAKE_CURRENT_LIST_DIR}/LoadGame.h
    ${CMAKE_CURRENT_LIST_DIR}/MainMenu.h
    ${CMAKE_CURRENT_LIST_DIR}/GamePlay.h
    ${CMAKE_CURRENT_LIST_DIR}/SaveLoader.hpp
  )

target_include_directories(states
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
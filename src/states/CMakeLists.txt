add_library(states "")

target_link_libraries(states
  PUBLIC
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML
    stateManager
    ecs
    utility
)

target_sources(states
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LoadGame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MainMenu.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GamePlay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SaveManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UiTest.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Game.h
    ${CMAKE_CURRENT_LIST_DIR}/LoadGame.h
    ${CMAKE_CURRENT_LIST_DIR}/MainMenu.h
    ${CMAKE_CURRENT_LIST_DIR}/GamePlay.h
    ${CMAKE_CURRENT_LIST_DIR}/SaveManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/UiTest.hpp
  )

target_include_directories(states
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
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
    ${CMAKE_CURRENT_LIST_DIR}/UiTest.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Game.hpp
  ${CMAKE_CURRENT_LIST_DIR}/LoadGame.hpp
  ${CMAKE_CURRENT_LIST_DIR}/MainMenu.hpp
  ${CMAKE_CURRENT_LIST_DIR}/GamePlay.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ImageLoader.hpp
  ${CMAKE_CURRENT_LIST_DIR}/UiTest.hpp	
  )

target_include_directories(states
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
add_library(states "")

target_link_libraries(states
  PUBLIC
    ImGui-SFML::ImGui-SFML
    stateManager
    ecs
)

target_sources(states
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Simulation.cpp
  PUBLIC
  
    ${CMAKE_CURRENT_LIST_DIR}/Game.h
    ${CMAKE_CURRENT_LIST_DIR}/Simulation.h
  )

target_include_directories(states
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
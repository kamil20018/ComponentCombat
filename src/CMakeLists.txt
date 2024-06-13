add_executable(game Source.cpp)

add_subdirectory(stateManager)
add_subdirectory(ecs)
add_subdirectory(states)

target_link_libraries(game
  PRIVATE
    ImGui-SFML::ImGui-SFML
    stateManager
    ecs
    states
  )

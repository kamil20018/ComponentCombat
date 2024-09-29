add_executable(game Source.cpp)

add_subdirectory(stateManager)
add_subdirectory(ecs)
add_subdirectory(states)
add_subdirectory(combatLog)
add_subdirectory(utility)

target_link_libraries(game
  PRIVATE
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML
    stateManager
    ecs
    states
    utility
    combatLog
  )

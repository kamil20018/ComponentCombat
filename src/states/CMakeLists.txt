add_library(states "")

target_link_libraries(states
  PUBLIC
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML
    stateManager
    ecs
    utility
)

file(GLOB fileCpp CONFIGURE_DEPENDS
  "*.cpp"
)

file(GLOB fileHpp CONFIGURE_DEPENDS
  "*.h"
  "*.hpp"
)

target_sources(states
  PRIVATE
    ${fileCpp}
  PUBLIC
    ${fileHpp}
  )

target_include_directories(states
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
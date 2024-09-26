add_library(ecs "")

target_link_libraries(ecs
  PUBLIC
    ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
    utility
    stateManager
    BT::behaviortree_cpp
)

file(GLOB_RECURSE fileCpp CONFIGURE_DEPENDS
  "*.cpp"
)

file(GLOB_RECURSE fileHpp CONFIGURE_DEPENDS
  "*.h"
  "*.hpp"
)

target_sources(ecs
  PRIVATE
    ${fileCpp}
  PUBLIC
    ${fileHpp}
  )


target_include_directories(ecs
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
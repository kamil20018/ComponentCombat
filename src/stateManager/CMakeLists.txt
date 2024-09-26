add_library(stateManager "")

target_link_libraries(stateManager
  PUBLIC
    ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
)

file(GLOB fileCpp CONFIGURE_DEPENDS
  "*.cpp"
)

file(GLOB fileHpp CONFIGURE_DEPENDS
  "*.h"
  "*.hpp"
)

target_sources(stateManager
  PRIVATE
    ${fileCpp}
  PUBLIC
    ${fileHpp}
  )

target_include_directories(stateManager
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
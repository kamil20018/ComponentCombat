add_library(utility "")

target_link_libraries(utility
  PUBLIC
    nlohmann_json::nlohmann_json
    ImGui-SFML::ImGui-SFML
)

file(GLOB fileCpp CONFIGURE_DEPENDS
  "*.cpp"
)

file(GLOB fileHpp CONFIGURE_DEPENDS
  "*.h"
  "*.hpp"
)

target_sources(utility
  PRIVATE
    ${fileCpp}
  PUBLIC
    ${fileHpp}
  )


target_include_directories(utility
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
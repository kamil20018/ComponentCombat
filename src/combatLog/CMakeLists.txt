add_library(combatLog "")

target_link_libraries(combatLog
  PUBLIC
    ImGui-SFML::ImGui-SFML
    utility
)

file(GLOB fileCpp CONFIGURE_DEPENDS
  "*.cpp"
)

file(GLOB fileHpp CONFIGURE_DEPENDS
  "*.h"
  "*.hpp"
)

target_sources(combatLog
  PRIVATE
    ${fileCpp}
  PUBLIC
    ${fileHpp}
  )

target_include_directories(combatLog
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
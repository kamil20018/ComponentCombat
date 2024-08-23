add_library(ecs "")

target_link_libraries(ecs
  PUBLIC
    ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
    utility
    stateManager
)

set(SystemPath ${CMAKE_CURRENT_LIST_DIR}/system)

target_sources(ecs
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
    ${SystemPath}/System.cpp
    ${SystemPath}/UiSystem.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Constants.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Component.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Registry.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Scene.hpp
    ${SystemPath}/System.hpp
    ${SystemPath}/UiSystem.cpp
  )

target_include_directories(ecs
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
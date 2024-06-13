add_library(ecs "")

target_link_libraries(ecs
  PUBLIC
    ImGui-SFML::ImGui-SFML
)

target_sources(ecs
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Component.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Scene.cpp
    ${CMAKE_CURRENT_LIST_DIR}/System.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Constants.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Component.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Registry.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Scene.hpp
    ${CMAKE_CURRENT_LIST_DIR}/System.hpp
  )

target_include_directories(ecs
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
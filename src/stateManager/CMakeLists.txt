add_library(stateManager "")

target_link_libraries(stateManager
  PUBLIC
    ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
)

target_sources(stateManager
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/StateManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/AssetManager.cpp
  PUBLIC
  
    ${CMAKE_CURRENT_LIST_DIR}/StateManager.h
    ${CMAKE_CURRENT_LIST_DIR}/AssetManager.h
    ${CMAKE_CURRENT_LIST_DIR}/State.h
    ${CMAKE_CURRENT_LIST_DIR}/Context.h
  )

target_include_directories(stateManager
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
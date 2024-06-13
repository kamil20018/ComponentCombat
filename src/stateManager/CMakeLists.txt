add_library(stateManager "")

target_sources(stateManager
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/StateManager.cpp
  PUBLIC
  
    ${CMAKE_CURRENT_LIST_DIR}/StateManager.h
    ${CMAKE_CURRENT_LIST_DIR}/State.h
  )

target_include_directories(stateManager
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
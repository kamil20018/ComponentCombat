message(STATUS "Fetching SFML...")

# No need to build audio and network modules
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)
set(BUILD_SHARED_LIBS OFF)  # Needed for windows

find_package(SFML COMPONENTS graphics)
if (SFML_FOUND)
    message("Using system SFML")
else()
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 2f11710abc5aa478503a7ff3f9e654bd2078ebab # 2.5.1
    )

    FetchContent_MakeAvailable(sfml)
endif()


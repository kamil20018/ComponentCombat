include(FetchContent)

find_package(nlohmann_json)
if (nlohmann_json_FOUND)
    message("Using system nlohmann_json")
else()
    FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
    FetchContent_MakeAvailable(json)
endif()

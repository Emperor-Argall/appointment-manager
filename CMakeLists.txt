cmake_minimum_required(VERSION 3.24)
project(csfinal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fix for GCC 15 + SFML inline variable ODR bug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-unique")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(csfinal WIN32
        main.cpp
)
target_link_libraries(csfinal PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)
target_link_options(csfinal PRIVATE -Wl,--allow-multiple-definition)
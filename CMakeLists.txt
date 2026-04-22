cmake_minimum_required(VERSION 3.30)

project(LinksAwakening LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# Dependencies
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Boost 1.90 REQUIRED COMPONENTS unit_test_framework)

message(STATUS "SDL2 version: ${SDL2_VERSION}")
message(STATUS "SDL2_image version: ${SDL2_image_VERSION}")
message(STATUS "Boost version: ${Boost_VERSION}")

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)
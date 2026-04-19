cmake_minimum_required(VERSION 3.16)

set(APP_NAME LinksAwakening)

project(${APP_NAME} LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/Source/*.cpp"
)

list(FILTER SOURCES EXCLUDE REGEX ".*/Source/Tests/.*")

add_executable(${APP_NAME} ${SOURCES})

# Include directories (your engine)
target_include_directories(${APP_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/Source"
    "${CMAKE_SOURCE_DIR}/Source/Engine"
    "${CMAKE_SOURCE_DIR}/Source/Player"
    "${CMAKE_SOURCE_DIR}/Source/Interfaces"
)

# SDL2 (macOS Homebrew)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(${APP_NAME} PRIVATE
    /opt/homebrew/opt/sdl2_image/include/SDL2/
    /opt/homebrew/opt/sdl2/include/SDL2
)

target_link_libraries(${APP_NAME} PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
)

# macOS system frameworks (required by SDL sometimes)
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(OPENGL_LIBRARY OpenGL)

    target_link_libraries(${APP_NAME} PRIVATE
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${OPENGL_LIBRARY}
    )
endif()

# Defines DEBUG and NDEBUG macros for Debug/Release
target_compile_definitions(${APP_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# Output directories for binaries
set_target_properties(${APP_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/Release"
)

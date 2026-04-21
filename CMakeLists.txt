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

# Default build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif ()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Source files
file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

list(FILTER SOURCES EXCLUDE REGEX ".*/src/tests/.*")

add_executable(${APP_NAME} ${SOURCES})

# Include directories
target_include_directories(${APP_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/core"
        "${CMAKE_SOURCE_DIR}/src/zelda_core"
        "${CMAKE_SOURCE_DIR}/src/interfaces"
)

# -------------------------
# Warnings (GCC/Clang)
# -------------------------
add_library(PROJECT_WARNINGS INTERFACE)

target_compile_options(PROJECT_WARNINGS INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Wnull-dereference
        -Wcast-align
        -Wcast-qual
        -Wold-style-cast
        -Woverloaded-virtual
        -Wnon-virtual-dtor
        -Wmisleading-indentation
        -Werror

        # Debug flags
        $<$<CONFIG:Debug>:-O0 -g -fsanitize=address,undefined>

        # Release flags
        $<$<CONFIG:Release>:-O2>
)

target_link_libraries(${APP_NAME} PRIVATE PROJECT_WARNINGS)

# Sanitizer link options (Debug only)
target_link_options(${APP_NAME} PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

# -------------------------
# SDL2
# -------------------------
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(${APP_NAME} PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
)

# -------------------------
# Defines
# -------------------------
target_compile_definitions(${APP_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

# -------------------------
# Output directories
# -------------------------
set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/Debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/Release"
)
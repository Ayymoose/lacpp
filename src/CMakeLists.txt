set(APP_NAME LinksAwakening)

project(${APP_NAME} LANGUAGES CXX)

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
        -Wno-c2y-extensions

        $<$<CONFIG:Debug>:-O0 -g -fsanitize=address,undefined>
        $<$<CONFIG:Release>:-O2>
)

target_link_options(PROJECT_WARNINGS INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

add_executable(${APP_NAME}
        app/Main.cpp
)

target_link_libraries(${APP_NAME} PRIVATE
        GAME_CORE
        PROJECT_WARNINGS
)

target_compile_definitions(${APP_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
)

set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/bin/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release
)

add_library(GAME_CORE STATIC
        core/Camera.cpp
        core/DataManager.cpp
        core/Engine.cpp
        core/Keyboard.cpp
        core/Renderer.cpp
        core/Resource.cpp
        core/ResourceManager.cpp
        core/Sprite.cpp
        core/Toggle.cpp
        core/Window.cpp
        core/SDL_RenderTarget.cpp
        core/Tilemap.cpp
        #
        zelda_core/Dialogue.cpp
        zelda_core/Inventory.cpp
        zelda_core/Link.cpp
        zelda_core/RoomLinkManager.cpp
        zelda_core/RoomManager.cpp
        zelda_core/TilemapManager.cpp
        zelda_core/Worldmap.cpp
        #
        zelda_gui/Dialogue.cpp
        zelda_gui/Inventory.cpp
        zelda_gui/Worldmap.cpp
)

target_include_directories(GAME_CORE PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src/zelda_core
        ${CMAKE_SOURCE_DIR}/src/zelda_gui
)

target_link_libraries(GAME_CORE PUBLIC
        PROJECT_WARNINGS
        SDL2::SDL2
        SDL2_image::SDL2_image
)
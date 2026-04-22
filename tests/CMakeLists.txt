enable_testing()

function(add_test_target name dir)
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
            ${CMAKE_SOURCE_DIR}/tests/${dir}/*.cpp
    )

    add_executable(${name} ${TEST_SOURCES})

    target_link_libraries(${name} PRIVATE
            Boost::unit_test_framework
            GAME_CORE
            PROJECT_WARNINGS
    )

    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_test_target(TEST_CORE core)
add_test_target(TEST_ZELDA_CORE zelda_core)
add_test_target(TEST_ZELDA_GUI zelda_gui)
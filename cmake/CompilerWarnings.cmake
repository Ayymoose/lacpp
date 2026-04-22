add_library(project_warnings INTERFACE)

target_compile_options(project_warnings INTERFACE
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

        $<$<CONFIG:Debug>:-O0 -g -fsanitize=address,undefined>
        $<$<CONFIG:Release>:-O2>
)

target_link_options(project_warnings INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)
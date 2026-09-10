add_library(mouse-clicker)

target_sources(mouse-clicker
    PRIVATE
        src/clicker.cpp
)

target_include_directories(mouse-clicker
    PUBLIC
        include
)

add_subdirectory(tests)
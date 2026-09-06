add_library(mouse-clicker)

target_sources(mouse-clicker
    PRIVATE
        clicker.cpp
)

target_include_directories(mouse-clicker
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(tests)
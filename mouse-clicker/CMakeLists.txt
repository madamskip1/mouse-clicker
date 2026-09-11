add_library(mouse-clicker)

target_sources(mouse-clicker
    PRIVATE
        src/clicker.cpp
        src/mouse-linux.cpp
)

target_include_directories(mouse-clicker
    PUBLIC
        include
)

find_package(X11 REQUIRED)

target_link_libraries(mouse-clicker
    PRIVATE
        X11::X11
        X11::Xtst
)

add_subdirectory(tests)
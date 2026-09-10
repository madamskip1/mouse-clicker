find_package(Qt6 COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
)

qt_add_executable(mouse-clicker-app
    src/main.cpp
    src/mainwindow.cpp

    include/mainwindow.hpp

    gui/mainwindow.ui
)

target_link_libraries(mouse-clicker-app
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(mouse-clicker-app
    PRIVATE
        include
)
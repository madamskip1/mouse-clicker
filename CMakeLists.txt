cmake_minimum_required(VERSION 3.14)

project(mouse-clicker)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)


add_subdirectory(mouse)
add_subdirectory(clicker)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
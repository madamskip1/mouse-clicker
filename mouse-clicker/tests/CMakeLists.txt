include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(mouse-clicker-tests)

target_sources(mouse-clicker-tests
    PRIVATE
        clicker-tests.cpp
)

target_link_libraries(mouse-clicker-tests
    PRIVATE
        mouse-clicker
        gtest_main
)

gtest_discover_tests(mouse-clicker-tests)
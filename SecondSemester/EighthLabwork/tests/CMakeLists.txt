cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        Tests
        Tests.cpp
)

target_link_libraries(
        Tests
        BSTContainer
        GTest::gtest_main
)

target_include_directories(Tests PUBLIC ../labwork8-sigris1)

include(GoogleTest)

gtest_discover_tests(Tests)
cmake_minimum_required(VERSION 3.12)

project(SimpleSearchEngine)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(lib)


enable_testing()
add_subdirectory(tests)
add_subdirectory(indexbin)
add_subdirectory(finderbin)
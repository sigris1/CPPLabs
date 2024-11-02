add_executable(Finder main.cpp)

target_link_libraries(Finder PRIVATE SSE)
target_include_directories(Finder PUBLIC ../../EighthLabwork)
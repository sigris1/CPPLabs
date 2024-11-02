add_executable(Indexator main.cpp)

target_link_libraries(Indexator PRIVATE SSE)
target_include_directories(Indexator PUBLIC ../../EighthLabwork)
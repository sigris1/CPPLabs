add_library(BSTContainer
        Tree.h
        Container.h
        Container.cpp
        Node.h
)

target_include_directories(BSTContainer PUBLIC "${PROJECT_SOURCE_DIR}/include")

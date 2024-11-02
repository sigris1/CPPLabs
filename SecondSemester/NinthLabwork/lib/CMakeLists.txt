add_library(STLAdapters
        Adapter.h
        Adapter.cpp
)

target_include_directories(STLAdapters PUBLIC "${PROJECT_SOURCE_DIR}/include")

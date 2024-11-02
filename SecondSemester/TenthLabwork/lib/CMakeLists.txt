add_library(scheduler
        Scheduler.cpp
        Scheduler.h
        BinaryTask.h
        UnaryTask.h
        Task.h
        My_any.h
)

target_include_directories(scheduler PUBLIC "${PROJECT_SOURCE_DIR}/include")

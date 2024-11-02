add_library(SSE
        finder/Parser.cpp
        finder/Parser.h
        finder/Node.h
        finder/Tree.cpp
        finder/Tree.h
        finder/BM25.cpp
        finder/Request.h
        finder/TF_IDF.cpp
        finder/FinderProcessor.cpp
        indexator/Ourdirectory.cpp
        indexator/Ourdirectory.h
        indexator/File.h
        indexator/File.cpp
        indexator/IndexInFile.h
        indexator/IndexatorProcessor.cpp
)

target_include_directories(SSE PUBLIC "Finder/include")
target_include_directories(SSE PUBLIC "Indexator/include")
//
// Created by sigris on 10.05.2024.
//
#pragma once
#include "vector"
#include "queue"
#include "File.h"

class OurDirectory {
    //friend void GetTF_IDF(OurDirectory& directory);
    //friend void DoBM25(OurDirectory& directory);
//    friend float CountingBFS(Node* start, float& result, File& file, OurDirectory& directory);
public:
    OurDirectory(const Request& request, char* directory)
            : directory_(directory)
            , now_(request)
    {}
    OurDirectory(const std::string& directory)
            : directory_(directory)
    {}
    void GetFileNames(const std::string& directory);
    void DoIndex(std::string index);
private:
    std::vector<File> files_;
    std::map<std::pair<std::string, std::string>, float> tf_idf_;
    std::string directory_;
    std::priority_queue<std::pair<float, File>> after_BM25_;
    Request now_;
};


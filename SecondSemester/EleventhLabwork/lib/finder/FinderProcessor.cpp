//
// Created by sigris on 10.05.2024.
//

#include "Request.h"
#include "Parser.h"
#include "fstream"
#include "queue"
#include "../indexator/File.h"
#include "TF_IDF.cpp"
#include "BM25.cpp"

void PrintInformationAboutIndex(char* result, std::priority_queue<std::pair<float, std::string>> after_BM25_, std::string& index, Request& request){
    std::ofstream file(result);
    int len = after_BM25_.size();
    for (int i = 0; i < len; ++i){
        file << (after_BM25_.top()).second << "\n";
        for (const auto &j : request.OccurrenceFrequency | std::views::keys){
            file << "word : " <<  j << "\n";
            std::fstream now((index + "/").append(j));
            std::string file_name;
            int str;
            int num;
            while (now >> file_name >> str >> num){
                if (file_name == (after_BM25_.top()).second){
                    file << "line position : " << str + 1 << ";  word position : " << num + 1 << "\n";
                }
            }
        }
        file << "\n";
        after_BM25_.pop();
    }
}

void FinderProcess(int argc, char* argv[]){
    std::string index_name = argv[0];
    Request now = GetRequest(argc - 2, argv + 2);
    std::map<std::pair<std::string, std::string>, float> tf_idf_ = GetTF_IDF(now, index_name);
    std::priority_queue<std::pair<float, std::string>> after_BM25_ = DoBM25(tf_idf_, now, index_name);
    PrintInformationAboutIndex(argv[1], after_BM25_, index_name, now);
}
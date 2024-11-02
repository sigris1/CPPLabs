//
// Created by sigris on 09.05.2024.
//

#include "../indexator/Ourdirectory.h"
#include "fstream"
#include "ranges"

float CountingBFS(Node* start, float& result, const std::string& file, std::map<std::pair<std::string, std::string>, float>& tf_idf){
    if (start->connection_type == 1){
        if (start->right_son != nullptr and start->left_son != nullptr){
            result = CountingBFS(start->right_son, result, file, tf_idf) + CountingBFS(start->left_son, result, file, tf_idf);
        } else if (start->right_son != nullptr){
            result = CountingBFS(start->right_son, result, file, tf_idf) + tf_idf[std::make_pair(file, start->left_value)];
        }else if (start->left_son != nullptr){
            result = CountingBFS(start->left_son, result, file, tf_idf) + tf_idf[std::make_pair(file, start->right_value)];
        } else {
            result = tf_idf[std::make_pair(file, start->right_value)] + tf_idf[std::make_pair(file, start->left_value)];
        }
    } else {
        if (start->right_son != nullptr and start->left_son != nullptr){
            result = std::min(CountingBFS(start->right_son, result, file, tf_idf), CountingBFS(start->left_son, result, file, tf_idf));
        } else if (start->right_son != nullptr){
            result = std::min(CountingBFS(start->right_son, result, file, tf_idf), tf_idf[std::make_pair(file, start->left_value)]);
        }else if (start->left_son != nullptr){
            result = std::min(CountingBFS(start->left_son, result, file, tf_idf), tf_idf[std::make_pair(file, start->right_value)]);
        } else {
            result = std::min(tf_idf[std::make_pair(file, start->right_value)], tf_idf[std::make_pair(file, start->left_value)]);
        }
    }
    return result;
}

std::priority_queue<std::pair<float, std::string>> DoBM25(std::map<std::pair<std::string, std::string>, float>& tf_idf, Request& request, std::string& index_name){
    std::fstream file_inf(index_name + "/words_numbers");
    std::priority_queue<std::pair<float, std::string>> after_BM25;
    std::map<std::string, int> counter;
    std::string name;
    int count;
    while (file_inf >> name >> count){
        counter[name] = count;
    }
    for (auto& i : counter | std::views::keys){
        float res = 0;
        CountingBFS(request.request_definition.root, res, i, tf_idf);
        if (res != 0){
            after_BM25.emplace(res, i);
        }
    }
    return after_BM25;
}
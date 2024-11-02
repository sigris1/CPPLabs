//
// Created by sigris on 10.05.2024.
//

#include "../indexator/Ourdirectory.h"
#include "istream"
#include "fstream"
#include "ranges"

std::map<std::pair<std::string, std::string>, float> GetTF_IDF(Request& request, std::string& index_name) {
    std::map<std::pair<std::string, std::string>, float> res;
    std::vector<std::string> null_words;
    std::fstream file_inf(index_name + "/words_numbers");
    std::map<std::string, int> counter;
    std::string name;
    int count;
    while (file_inf >> name >> count){
        counter[name] = count;
    }
    for (auto& i : request.request_definition.words){
        std::string now_name = (index_name + '/').append(i);
        std::fstream now(now_name.c_str());
        if (!now.is_open()){
            null_words.push_back(i);
        } else {
            std::string current;
            int str;
            int num;
            std::map<std::string, std::vector<std::pair<int, int>>> ans;
            while (now >> current >> str >> num ){
                ans[current].emplace_back(str, num);
            }
            for (auto& j : counter | std::views::keys){
                if (ans.contains(j)){
                    float tf = (float)ans[j].size() / (float)counter[j];
                    float idf = log(counter.size() / ans.size()) + 1;
                    res[std::make_pair(j, i)] = tf * idf;
                } else {
                    res[std::make_pair(j, i)] = 0;
                }
            }
        }
    }
    for (auto & i : null_words){
        for (auto& j : counter | std::views::keys){
            res[std::make_pair(j, i)] = 0;
        }
    }
    return res;
}

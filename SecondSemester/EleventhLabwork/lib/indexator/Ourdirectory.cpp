//
// Created by sigris on 10.05.2024.
//

#include "Ourdirectory.h"
#include "filesystem"
#include "fstream"
#include "sstream"
#include "iostream"

void OurDirectory::GetFileNames(const std::string& directory) {
    for (const auto& file : std::filesystem::directory_iterator(directory)){
        if (std::filesystem::is_directory(file)){
            GetFileNames(file.path().string());
        } else {
            File now(file.path().string(), now_);
            files_.push_back(now);
        }
    }
}



void PrintInfoMap(std::map<std::string, std::vector<IndexInFile>>& current, std::string& index_name){
    for (auto& i : current){
        std::string cur = i.first;
        if (cur.empty()){
            continue;
        }
        std::ofstream file((index_name + "/").append(cur), std::ios::app);
        for (auto& j : i.second){
            file << j.file_name << " " << j.string_number << " " << j.word_number << "\n";
        }
    }
}


void OurDirectory::DoIndex(std::string index) {
    std::filesystem::create_directory(index);
    std::ofstream words_in_file(index + '/' + "words_numbers", std::ios::app);
    std::map<std::string, std::vector<IndexInFile>> current;
    int num = 0;
    for (File & i : files_) {
        num++;
        std::ifstream file(i.file_name);
        int line_number = 0;
        for (std::string line; std::getline(file, line);) {
            int word_number = 0;
            char *word = std::strtok(line.data(), "\t!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~' '");
            while (word != nullptr) {
                std::string current_word = word;
                current[current_word].emplace_back(i.file_name, line_number, word_number);
                word_number++;
                word = std::strtok(nullptr, "\t!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~' '");
                i.words_count++;
            }
            line_number++;
            if (current.size() >= 100000000){
                PrintInfoMap(current, index);
                current.clear();
            }
        }
        words_in_file << i.file_name << " " << i.words_count << "\n";
    }
    PrintInfoMap(current, index);
}

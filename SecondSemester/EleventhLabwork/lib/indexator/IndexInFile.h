#include <utility>

//
// Created by sigris on 10.05.2024.
//

#pragma once

struct IndexInFile{
    IndexInFile(std::string& name, int string_num, int word_num)
            : file_name(name)
            , string_number(string_num)
            , word_number(word_num)
    {}
    std::string file_name;
    int string_number;
    int word_number;
};

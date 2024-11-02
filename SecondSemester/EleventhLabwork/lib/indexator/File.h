//
// Created by sigris on 10.05.2024.
//

#pragma once

#include "map"
#include "../finder/Request.h"

class File {
    friend class OurDirectory;
public:
    File(std::string  file_name, const Request& request);
    ~File() = default;
    bool operator<(const File& other) const;
    std::string file_name;
    int words_count = 0;
};
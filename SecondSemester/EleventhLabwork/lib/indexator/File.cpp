//
// Created by sigris on 10.05.2024.
//

#include "File.h"
#include <utility>
#include "fstream"

File::File(std::string file_name, const Request &request)
        : file_name(std::move(file_name))
        {}

bool File::operator<(const File& other) const{
    return this->file_name < other.file_name;
}
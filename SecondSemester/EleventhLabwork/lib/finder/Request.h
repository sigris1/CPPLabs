//
// Created by sigris on 09.05.2024.
//

#pragma once

#include "Tree.h"
#include "map"
#include "../indexator/IndexInFile.h"

struct Request{
    Request& operator=(const Request& other)= default;
    Tree request_definition;
    std::map<std::string, std::vector<IndexInFile>> OccurrenceFrequency;
};


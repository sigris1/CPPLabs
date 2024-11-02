//
// Created by sigris on 10.05.2024.
//

#include "Ourdirectory.h"

void IndexatorProcess(const std::string& directory, const std::string& index_path){
    OurDirectory current(directory);
    current.GetFileNames(directory);
    current.DoIndex(index_path);
}


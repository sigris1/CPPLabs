//
// Created by sigris on 01.05.2024.
//

#pragma once

#include "Node.h"

class Tree{
public:
    Tree() = default;
    Tree(const Tree& other) = default;
    ~Tree()= default;
    Tree& operator=(const Tree& other) = default;
    bool operator!=(const Tree& other);
    uint64_t size = 0;
    Node* root = nullptr;
    void AddValue(Node* position, bool is_left, const std::string& value, int number_in_req);
    void AddNode(Node* position, bool is_left, int connect_type, int number_in_req);
    std::vector<std::string> words;
};

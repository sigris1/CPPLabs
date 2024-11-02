//
// Created by sigris on 01.05.2024.
//

#pragma once

#include "cstdint"
#include "string"

class Node{
public:
    Node() = default;

    Node& operator=(const Node& other){
        if (this == &other){
            return *this;
        }
        connection_type = other.connection_type;
        parent = other.parent;
        left_son = other.left_son;
        right_son = other.right_son;
        left_value = other.left_value;
        right_value = other.right_value;
        return *this;
    }

    ~Node() = default;

    uint64_t number_in_request = 0;
    uint8_t connection_type = 1; // If two tokens are connected by AND then connection_type == 2, and if by OR then == 1
    Node* parent = nullptr;
    Node* left_son = nullptr;
    Node* right_son = nullptr;
    std::string left_value;
    std::string right_value;
};
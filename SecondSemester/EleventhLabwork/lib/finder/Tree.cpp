//
// Created by sigris on 01.05.2024.
//

#include "Tree.h"

void Tree::AddValue(Node* position, bool is_left, const std::string& value, int number_in_req) {
    if (is_left){
        position->left_value = value;
    } else {
        position->right_value = value;
    }
    words.push_back(value);
    size++;
}

void Tree::AddNode(Node* position, bool is_left, int connect_type, int number_in_req) {
    if (position == nullptr){
        root = new Node;
        root->connection_type = connect_type;
        root->number_in_request = number_in_req;
    } else if (is_left){
        position->left_son = new Node;
        position->left_son->connection_type = connect_type;
        position->left_son->parent = position;
        position->left_son->number_in_request = number_in_req;
    } else {
        position->right_son = new Node;
        position->right_son->connection_type = connect_type;
        position->right_son->parent = position;
        position->right_son->number_in_request = number_in_req;
    }
    size++;
}










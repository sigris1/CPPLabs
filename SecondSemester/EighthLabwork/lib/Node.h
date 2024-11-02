//
// Created by sigris on 06.03.2024.
//

#pragma once

template<typename T>
class Node{
public:
    Node()= default;
    explicit Node(T definition){
        value = definition;
    }
    Node<T>& operator=(Node<T>& other){
        value = other.value;
        parent = other.parent;
        right_son = other.right_son;
        left_son = other.left_son;
    }
    T value;
    Node* parent;
    Node* right_son = nullptr;
    Node* left_son = nullptr;
};

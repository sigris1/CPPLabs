
//
// Created by sigris on 01.03.2024.
//

#pragma once
#include <string>
#include "cstdint"
#include "iostream"
#include "Node.h"

template<typename T>
class Tree {
public:
    Node<T>* root = nullptr;

    uint64_t size = 0;

    explicit Tree<T>(const std::vector<T>& definitions){
        for (const auto& i : definitions){
            AddValue(i);
        }
        SetPositions();
    }

    Tree()= default;

    Tree<T>(const Tree<T>& old_tree)
            :size(old_tree.size)
            ,root(old_tree.root)
            , inorder_position_(old_tree.inorder_position_)
            , postorder_position_(old_tree.postorder_position_)
            , preorder_position_(old_tree.preorder_position_)
    {}

    Tree<T>& operator=(const Tree<T>& copied_tree){
        if (&copied_tree == this){
            return *this;
        }
        root = copied_tree.root;
        size = copied_tree.size;
        inorder_position_ = copied_tree.inorder_position_;
        preorder_position_ = copied_tree.preorder_position_;
        postorder_position_ = copied_tree.postorder_position_;
        return *this;
    }

    void AddValue(T value){
        auto* now = new Node<T>;
        now->value = value;
        if (size == 0){
            size++;
            now->value = value;
            root = now;
        } else {
            size++;
            Node<T>* place = root;
            while (true){
                if (place->left_son != nullptr && place->value > value){
                    place = place->left_son;
                } else if (place->left_son == nullptr && place->value > value){
                    place->left_son = now;
                    now->parent = place;
                    break;
                } else if (place->right_son != nullptr && place->value < value){
                    place = place->right_son;
                } else if (place->right_son == nullptr && place->value < value){
                    place->right_son = now;
                    now->parent = place;
                    break;
                }
            }
        }
    }

    void AddValue(Node<T>* now, T value){
        now->value = value;
        if (size == 0){
            size++;
            now->value = value;
            root = now;
        } else {
            size++;
            Node<T>* place = root;
            while (true){
                if (place->left_son != nullptr && place->value > value){
                    place = place->left_son;
                } else if (place->left_son == nullptr && place->value > value){
                    place->left_son = now;
                    now->parent = place;
                    break;
                } else if (place->right_son != nullptr && place->value < value){
                    place = place->right_son;
                } else if (place->right_son == nullptr && place->value < value){
                    place->right_son = now;
                    now->parent = place;
                    break;
                }
            }
        }
    }

    Node<T>* FindValue(T value){
        Node<T>* place = root;
        if (size == 0){
            return nullptr;
        } else {
            while(true) {
                if (place->value == value) {
                    return place;
                } else if (place->value > value && place->left_son != nullptr) {
                    place = place->left_son;
                } else if (place->value < value && place->right_son != nullptr){
                    place = place->right_son;
                } else {
                    return nullptr;
                }
            }
        }
    }

    Node<T>* cur_prev_node(Node<T>* now){
        if (now->left_son != nullptr){
            now = now->left_son;
            while (now->right_son != nullptr){
                now = now->right_son;
            }
            return now;
        }
        Node<T>* returned = now->parent;
        while (returned != nullptr && returned->left_son == now){
            now = now->parent;
            returned = returned->parent;
        }
        return returned;
    }

    Node<T>* cur_next_node(Node<T>* now){
        if (now->right_son != nullptr){
            now = now->right_son;
            while (now->left_son != nullptr){
                now = now->left_son;
            }
            return now;
        }
        if (now->parent == nullptr){
            return nullptr;
        }
        Node<T>* returned = now->parent;
        while (returned != nullptr && returned->right_son == now){
            now = now->parent;
            returned = returned->parent;
        }
        return returned;
    }

    Node<T>* next(Node<T>* now, T value){
        if (now == nullptr){
            return nullptr;
        }
        Node<T>* current_prev = cur_prev_node(now);
        Node<T>* current_next = cur_next_node(now);
        if (now->value <= value && current_next == nullptr){
            return nullptr;
        }
        if (now->value <= value && current_next->value <= value){
            return next(current_next, value);
        }
        if (now->value <= value && current_next->value > value){
            return current_next;
        }
        if (now->value > value && current_prev == nullptr){
            return now;
        }
        if (now->value > value && current_prev->value <= value){
            return now;
        }
        if (now->value > value && current_prev->value > value){
            return next(current_prev, value);
        }
        return nullptr;
    }

    Node<T>* prev(Node<T>* now, T value){
        if (now == nullptr){
            return nullptr;
        }
        Node<T>* current_prev = cur_prev_node(now);
        Node<T>* current_next = cur_next_node(now);
        if (now->value >= value && current_prev == nullptr){
            return nullptr;
        }
        if (now->value >= value && current_prev->value >= value){
            return prev(current_prev, value);
        }
        if (now->value >= value && current_prev->value < value){
            return current_prev;
        }
        if (now->value <= value && current_next == nullptr){
            return now;
        }
        if (now->value <= value && current_next->value >= value){
            return now;
        }
        if (now->value < value && current_next->value < value){
            return prev(current_next, value);
        }
        return nullptr;
    }

    void DeleteValue(T value){
        if (size > 1){
            size--;
            Node<T>* place = root;
            if (root->value == value){
                if (place->left_son == nullptr){
                    root = place->right_son;
                    place->right_son->parent = nullptr;
                } else if (place->right_son == nullptr){
                    root = place->left_son;
                    place->left_son->parent = nullptr;
                } else {
                    Node<T>* pos = next(root, value);
                    T temp = pos->value;
                    DeleteValue(pos->value);
                    place->value = temp;
                }
            } else {
                while (true){
                    if (place->value > value && place->left_son != nullptr) {
                        place = place->left_son;
                    }
                    if (place->value < value && place->right_son != nullptr) {
                        place = place->right_son;
                    }
                    if (place->value == value){
                        break;
                    }
                }
                if (place->value != root->value && place->value == value) {
                    if (place->right_son == nullptr && place->left_son == nullptr) {
                        if (place->parent->left_son == place) {
                            place->parent->left_son = nullptr;
                        } else {
                            place->parent->right_son = nullptr;
                        }
                    } else if (place->right_son == nullptr && place->left_son != nullptr) {
                        if (place->parent->left_son == place) {
                            place->parent->left_son = place->left_son;
                            place->left_son->parent = place->parent;
                        } else {
                            place->parent->right_son = place->left_son;
                            place->left_son->parent = place->parent;
                        }
                    } else if (place->right_son != nullptr && place->left_son == nullptr) {
                        if (place->parent->left_son == place) {
                            place->parent->left_son = place->right_son;
                            place->right_son->parent = place->parent;
                        } else {
                            place->parent->right_son = place->right_son;
                            place->right_son->parent = place->parent;
                        }
                    } else if (place->left_son != nullptr && place->right_son != nullptr) {
                        Node<T>* pos = next(root, value);
                        T temp = pos->value;
                        DeleteValue(pos->value);
                        place->value = temp;
                    }
                }
            }
        } else if (size == 1){
            if (root->value == value) {
                root = nullptr;
                size--;
            }
        }
    }

    Node<T>& NextPreorder(){
        if (preorder_position_->left_son != nullptr){
            preorder_position_ = preorder_position_->left_son;
        } else if (preorder_position_->right_son != nullptr){
            preorder_position_ = preorder_position_->right_son;
        } else {
            while (preorder_position_ == preorder_position_->parent->right_son){
                preorder_position_ = preorder_position_->parent;
            }
            while (preorder_position_ == preorder_position_->parent->left_son && preorder_position_->parent->right_son == nullptr && preorder_position_->parent != nullptr){
                preorder_position_ = preorder_position_->parent;
            }
            preorder_position_ = preorder_position_->parent;
            preorder_position_ = preorder_position_->right_son;
        }
        return *preorder_position_;
    }

    Node<T>& PrevPreorder(){
        if (preorder_position_->parent == root && root->right_son == preorder_position_){
            if (root->left_son != nullptr){
                preorder_position_ = root->left_son;
                while (preorder_position_->right_son != nullptr){
                    preorder_position_ = preorder_position_->right_son;
                }
                return *preorder_position_;
            } else {
                preorder_position_ = root;
            }
        }
        if (preorder_position_ == preorder_position_->parent->left_son){
            preorder_position_ = preorder_position_->parent;
        } else {
            preorder_position_ = preorder_position_->parent;
            if (preorder_position_->left_son != nullptr){
                preorder_position_ = preorder_position_->left_son;
                while (preorder_position_->right_son != nullptr){
                    preorder_position_ = preorder_position_->right_son;
                }
            }
        }
        return *preorder_position_;
    }

    Node<T>& NextPostorder(){
        if (postorder_position_->parent != nullptr){
            if (postorder_position_->parent->right_son != postorder_position_) {
                postorder_position_ = postorder_position_->parent;
                if (postorder_position_->right_son == nullptr) {
                    return *postorder_position_;
                } else {
                    postorder_position_ = postorder_position_->right_son;
                    while (postorder_position_->right_son != nullptr || postorder_position_->left_son != nullptr) {
                        if (postorder_position_->left_son != nullptr) {
                            postorder_position_ = postorder_position_->left_son;
                        } else {
                            postorder_position_ = postorder_position_->right_son;
                        }
                    }
                }
            } else {
                postorder_position_ = postorder_position_->parent;
            }
        }
        return *postorder_position_;
    }

    Node<T>& PrevPostorder(){
        if (postorder_position_->right_son != nullptr){
            postorder_position_ = postorder_position_->right_son;
        } else if (postorder_position_->left_son != nullptr){
            postorder_position_ = postorder_position_->left_son;
        } else {
            while (true){
                if (postorder_position_ == root){\
                    if (root->left_son != nullptr) {
                        postorder_position_ = root->left_son;
                    }
                } else if (postorder_position_ == postorder_position_->parent->right_son && postorder_position_->parent->left_son != nullptr){
                    postorder_position_ = postorder_position_->parent->left_son;
                    break;
                } else {
                    postorder_position_ = postorder_position_->parent;
                }
            }
        }
        return *postorder_position_;
    }

    Node<T>& NextInorder(){
        if (inorder_position_->right_son != nullptr){
            inorder_position_ = inorder_position_->right_son;
            while (inorder_position_->left_son != nullptr){
                inorder_position_ = inorder_position_->left_son;
            }
            return *inorder_position_;
        }
        Node<T>* now = inorder_position_->parent;
        while (now != nullptr && now->right_son == inorder_position_){
            inorder_position_ = now;
            now = now->parent;
        }
        inorder_position_ = now;
        return *inorder_position_;
    }

    Node<T>& PrevInorder(){
        if (inorder_position_->left_son != nullptr){
            inorder_position_ = inorder_position_->left_son;
            while (inorder_position_->right_son != nullptr){
                inorder_position_ = inorder_position_->right_son;
            }
            return *inorder_position_;
        }
        Node<T>* now = inorder_position_->parent;
        while (now != nullptr && now->left_son == inorder_position_){
            inorder_position_ = inorder_position_->parent;
            now = now->parent;
        }
        inorder_position_ = now;
        return *inorder_position_;
    }

    void SetPositions(){
        preorder_position_ = root;
        Node<T>* now = root;
        while(now->left_son != nullptr){
            now = now->left_son;
        }
        inorder_position_ = now;
        postorder_position_ = now;
    }

private:
    Node<T>* inorder_position_ = nullptr;
    Node<T>* preorder_position_ = nullptr;
    Node<T>* postorder_position_ = nullptr;
};
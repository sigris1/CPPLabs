//
// Created by sigris on 05.03.2024.
//

#pragma once
#include "Tree.h"

template<class T, class Allocator = std::allocator<T>, class Comparator = std::less<>>
class Container {
public:
    class Iterator {
        friend class Container;
    public:
        std::string traversal_type;

        Node<T>* now = nullptr;

        Iterator(){
            now = nullptr;
            traversal_type = " ";
        }

        Iterator(Node<T>* pos){
            now = pos;
        }

        Iterator& operator=(const Iterator iter){
            traversal_type = iter.traversal_type;
            now = iter.now;
            father_ = iter.father_;
            return *this;
        }

        Iterator& operator--() {
            if (traversal_type == "pre") {
                now = &father_->tree_->PrevPreorder();
            } else if (traversal_type == "in") {
                now = &father_->tree_->PrevInorder();
            } else if (traversal_type == "post"){
                now = &father_->tree_->PrevPostorder();
            } else {
                std::cerr << "Set real traversal";
            }
            return *this;
        }

        Iterator& operator--(int) {
            if (traversal_type == "pre") {
                now = &father_->tree_->PrevPreorder();
            } else if (traversal_type == "in") {
                now = &father_->tree_->PrevInorder();
            } else if (traversal_type == "post"){
                now = &father_->tree_->PrevPostorder();
            } else {
                std::cerr << "Set real traversal";
            }
            return *this;
        }

        Iterator& operator++() {
            if (traversal_type == "pre") {
                now = &father_->tree_->NextPreorder();
            } else if (traversal_type == "in") {
                now = &father_->tree_->NextInorder();
            } else if (traversal_type == "post"){
                now = &father_->tree_->NextPostorder();
            } else {
                std::cerr << "Set real traversal";
            }
            return *this;
        };

        Iterator& operator++(int){
            if (traversal_type == "pre") {
                now = &father_->tree_->NextPreorder();
            } else if (traversal_type == "in") {
                now = &father_->tree_->NextInorder();
            } else if (traversal_type == "post"){
                now = &father_->tree_->NextPostorder();
            } else {
                std::cerr << "Set real traversal";
            }
            return *this;
        }

        Iterator& operator=(const T changed_value) {
            father_->tree_->DeleteValue(now->value);
            father_->tree_->AddValue(changed_value);
            now = father_->tree_->FindValue(changed_value);
            if (traversal_type == "pre") {
                father_->tree_->preorder_position_ = now;
            } else if (traversal_type == "in") {
                father_->tree_->inorder_position_ = now;
            } else  if (traversal_type == "post"){
                father_->tree_->postorder_position_ = now;
            } else {
                std::cerr << "Set real traversal";
            }
        }

        bool operator==(Iterator& other){
            if (now == other.now && traversal_type == other.traversal_type && father_ == other.father_){
                return true;
            }
            return false;
        }

        T operator*(){
            return now->value;
        }
    private:
        Container* father_;
    };

    Container(Tree<T>& tree, std::string& traversal_type){
        tree_ = &tree;
        test_node_ = std::allocator_traits<decltype(allocForNode_)>::allocate(allocForNode_,1);
        Iterator iter;
        iterator = iter;
        iterator.traversal_type = traversal_type;
        iterator.father_ = this;
        SetTestNode();
    }

    Container& operator=(const Container& other){
        if (&other == this){
            return *this;
        }
        begin_ = other.begin_;
        end_ = other.end_;
        iterator = other.iterator;
        tree_ = other.tree_;
        test_node_ = other.test_node_;
    }

    ~Container(){
        DeleteTree_(tree_->root);
    }

    bool operator==(Container& other){
        if (tree_ != other.tree_){
            return false;
        }
        if (iterator.traversal_type != other.iterator.traversal_type){
            return false;
        }
        return true;
    }

    bool operator!=(Container& other){
        return !(this == other);
    }

    void DeallocateNode(Node<T>* node){
        std::allocator_traits<decltype(allocForNode_)>::destroy(allocForNode_, node);
    };

    void SetTestNode(){
        if (tree_->size == 0){
            test_node_ = tree_->root;
            begin_ = tree_->root;
            end_ = tree_->root;
        }
        if (iterator.traversal_type == "pre") {
            test_node_->left_son = tree_->root;
            Node<T>* position = tree_->root;
            while (position->right_son != nullptr || position->left_son != nullptr){
                if (position->right_son != nullptr){
                    position = position->right_son;
                    continue;
                } else {
                    position = position->left_son;
                    continue;
                }
            }
            test_node_->right_son = position;
        } else if (iterator.traversal_type == "in") {
            Node<T>* max = tree_->root;
            while (max->right_son != nullptr){
                max = max->right_son;
            }
            Node<T>* min = tree_->root;
            while (min->left_son != nullptr){
                min = min->left_son;
            }
            test_node_->left_son = min;
            test_node_->right_son = max;
        } else {
            Node<T>* min = tree_->root;
            while (min->left_son != nullptr){
                min = min->left_son;
            }
            test_node_->left_son = min;
            test_node_->right_son = tree_->root;
        }
        begin_ = test_node_;
        end_ = test_node_;
    }

    void RedeclareTraversal(std::string& new_traversal_type) {
        iterator.traversal_type = new_traversal_type;
        SetTestNode();
    }

    void push_back(const T added_value) {
        Node<T>* node = std::allocator_traits<decltype(allocForNode_)>::allocate(allocForNode_,1);
        tree_->AddValue(node, added_value);
        SetTestNode();
    }

    void delete_value(const T deleted_value) {
        Node<T>* node = tree_->FindValue(deleted_value);
        tree_->DeleteValue(deleted_value);
        DeallocateNode(node);
    }

    bool find_value(const T value) {
        if (tree_->FindValue(value) != nullptr){
            return true;
        } else {
            return false;
        }
    }

    bool empty(){
        return tree_->size == 0;
    }

    size_t size(){
        return tree_->size;
    }

    Comparator key_comp(){
        return Comparator();
    }

    Comparator value_comp(){
        return Comparator();
    }

    bool contains(T value){
        return find_value(value);
    }

    size_t count(T value){
        if (contains(value)){
            return 1;
        } else {
            return 0;
        }
    }

    Iterator begin(){
        return begin_;
    }

    Iterator cbegin() const {
        return begin_;
    }

    Iterator rbegin(){
        return std::reverse_iterator(begin_);
    }

    Iterator end(){
        return end_;
    }

    Iterator cend() const{
        return end_;
    }

    Iterator rend(){
        return std::reverse_iterator(end_);
    }

    void swap(Container& other){
        std::swap(other.tree_, tree_);
        std::swap(other.test_node_, test_node_);
        std::swap(other.iterator, iterator);
        std::swap(other.end_, end_);
        std::swap(other.begin_, begin_);
        std::swap(other.allocForNode_, allocForNode_);
        std::swap(other.alloc_, alloc_);
        SetTestNode();
        other.SetTestNode();
    }

    void clear(){
        DeleteTree_(tree_->root);
    }

    void merge(Container& other){
        while(!other.empty()){
            push_back(other.iterator.now);
            other.delete_value(other.iterator.now);
        }
    }

    size_t erase(Iterator iter){
        return erase(*iter);
    }

    size_t erase(const Iterator iter) const{
        return erase(*iter);
    }

    Iterator lower_bound(T value){
        return Iterator(find_value(value));
    }

    Iterator lower_bound(T value) const{
        return Iterator(find_value(value));
    }

    Iterator upper_bound(T value){
        return Iterator(find_value(value)++);
    }

    Iterator upper_bound(T value) const{
        return Iterator(find_value(value)++);
    }

    std::pair<Iterator, Iterator> equal_range(T value){
        return std::make_pair(lower_bound(value), upper_bound(value));
    };

    std::pair<Iterator, Iterator> equal_range(T value) const{
        return std::make_pair(lower_bound(value), upper_bound(value));
    };

    Iterator iterator;
private:
    Tree<T>* tree_ = nullptr;
    Allocator alloc_;
    std::allocator_traits<decltype(alloc_)>::template rebind_alloc<Node<T>> allocForNode_;
    Node<T>* test_node_ = nullptr;
    void DeleteTree_(Node<T>* now){
        if (now->left_son != nullptr){
            DeallocateNode(now->left_son);
        }
        if (now->right_son != nullptr){
            DeallocateNode(now->right_son);
        }
        DeallocateNode(now);
    }
    Iterator begin_ = Iterator(test_node_);
    Iterator end_ = Iterator(test_node_);
};
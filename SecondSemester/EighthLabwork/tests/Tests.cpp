//
// Created by sigris on 01.03.2024.
//
/*
 *
 * Дерево для тестов функционала
 *
 *                  8
 *            /          \
 *           /            \
 *          3              10
 *        /   \             \
 *       /     \             \
 *     1        6             14
 **           /   \          /
 *           /     \        /
 *          4       7      13
 *
 * Ожидаемые обходы:
 * in 1 3 4 6 7 8 10 13 14
 * post 1 4 7 6 3 13 14 10 8
 * pre 8 3 1 6 4 7 10 14 13
 * */

#include "gtest/gtest.h"
#include "../lib/Container.h"
#include "vector"

std::string kPreorderTraversal = "pre";
std::string kInorderTraversal = "in";
std::string kPostorderTraversal = "post";

void CreateTreeForTest(std::vector<int>& first_tested_tree){
    first_tested_tree.push_back(8);
    first_tested_tree.push_back(3);
    first_tested_tree.push_back(1);
    first_tested_tree.push_back(6);
    first_tested_tree.push_back(4);
    first_tested_tree.push_back(7);
    first_tested_tree.push_back(10);
    first_tested_tree.push_back(14);
    first_tested_tree.push_back(13);
}


TEST(TreeTestSuite, StartEndTests){
    std::vector<int> first_tested_tree;
    CreateTreeForTest(first_tested_tree);
    Tree<int> tree(first_tested_tree);
    Container<int> container(tree, kPreorderTraversal);
    uint64_t prebegin = container.begin().now->left_son->value;
    uint64_t preend = container.end().now->right_son->value;
    container.RedeclareTraversal(kInorderTraversal);
    uint64_t inbegin = container.begin().now->left_son->value;
    uint64_t inend = container.end().now->right_son->value;
    container.RedeclareTraversal(kPostorderTraversal);
    uint64_t postbegin = container.begin().now->left_son->value;
    uint64_t postend = container.end().now->right_son->value;
    ASSERT_EQ(prebegin, 8);
    ASSERT_EQ(preend, 13);
    ASSERT_EQ(postbegin, 1);
    ASSERT_EQ(postend, 8);
    ASSERT_EQ(inbegin, 1);
    ASSERT_EQ(inend, 14);
}

TEST(TreeTestSuite, Nextvalue){
    std::vector<int> first_tested_tree;
    CreateTreeForTest(first_tested_tree);
    Tree<int> tree(first_tested_tree);
    Container<int> container(tree, kPreorderTraversal);
    ++container.iterator;
    uint64_t preorder_place = *container.iterator;
    container.RedeclareTraversal(kInorderTraversal);
    uint64_t inorder_place;
    for (uint64_t i = 0; i < 2; ++i){
        ++container.iterator;
        inorder_place = *container.iterator;
    }
    uint64_t postorder_place;
    container.RedeclareTraversal(kPostorderTraversal);
    for (uint64_t i = 0; i < 3; ++i){
        ++container.iterator;
        postorder_place = container.iterator.now->value;
    }
    ASSERT_EQ(preorder_place, 3);
    ASSERT_EQ(inorder_place, 4);
    ASSERT_EQ(postorder_place, 6);
}

TEST(TreeTestSuite, PrevValue){
    std::vector<int> first_tested_tree;
    CreateTreeForTest(first_tested_tree);
    Tree<int> tree(first_tested_tree);
    Container<int> container(tree, kPreorderTraversal);
    ++container.iterator;
    --container.iterator;
    uint64_t preorder_place = container.iterator.now->value;
    container.RedeclareTraversal(kInorderTraversal);
    uint64_t inorder_place;
    for (uint64_t i = 0; i < 7; ++i){
        ++container.iterator;
        inorder_place = container.iterator.now->value;
    }
    for (uint64_t i = 0; i < 3; ++i){
        --container.iterator;
        inorder_place = container.iterator.now->value;
    }
    uint64_t postorder_place;
    container.RedeclareTraversal(kPostorderTraversal);
    for (uint64_t i = 0; i < 5; ++i){
        ++container.iterator;
        postorder_place = container.iterator.now->value;
    }
    for (uint64_t i = 0; i < 2; ++i){
        --container.iterator;
        postorder_place = container.iterator.now->value;
    }
    ASSERT_EQ(preorder_place, 8);
    ASSERT_EQ(inorder_place, 7);
    ASSERT_EQ(postorder_place, 6);
}

TEST(TreeTestSuite, AddValue){
    std::vector<int> first_tested_tree;
    CreateTreeForTest(first_tested_tree);
    Tree<int> tree(first_tested_tree);
    Container<int> container(tree, kInorderTraversal);
    container.push_back(2);
    ++container.iterator;
    uint64_t inorder_place = container.iterator.now->value;
    ASSERT_EQ(inorder_place, 2);
}

TEST(TreeTestSuite, DeleteValue){
    std::vector<int> first_tested_tree;
    CreateTreeForTest(first_tested_tree);
    Tree<int> tree(first_tested_tree);
    Container<int> container(tree, kPostorderTraversal);
    container.delete_value(6);
    uint64_t postorder_place;
    container.RedeclareTraversal(kPostorderTraversal);
    for (uint64_t i = 0; i < 5; ++i){
        ++container.iterator;
        postorder_place = container.iterator.now->value;
    }
    for (uint64_t i = 0; i < 2; ++i){
        --container.iterator;
        postorder_place = container.iterator.now->value;
    }
    ASSERT_EQ(postorder_place, 3);
}

TEST(TreeTestSuite, ExistValue){
    std::vector<int> first_tested_tree;
    CreateTreeForTest(first_tested_tree);
    Tree<int> tree(first_tested_tree);
    Container<int> container(tree, kPostorderTraversal);
    bool is_exist_5 = container.find_value(5);
    bool is_exist_6 = container.find_value(6);
    ASSERT_EQ(is_exist_5, false);
    ASSERT_EQ(is_exist_6, true);
}
//
// Created by sigris on 23.03.2024.
//

#include "gtest/gtest.h"
#include "../lib/Adapter.h"

TEST(Adapters, reverse){
    std::vector<int> before = {1, 2, 3, 4, 5, 6};
    auto after = before | reverse();
    int position = 6;
    for (int & i : after){
        ASSERT_EQ(i, position);
        --position;
    }
}

TEST(Adapters, drop){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | drop(5) ;
    int position = 6;
    for (int & i : after){
        ASSERT_EQ(i, position);
        ++position;
    }
}

TEST(Adapters, take){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | take(5);
    int position = 1;
    for (int & i : after){
        ASSERT_EQ(i, position);
        ++position;
    }
}

TEST(Adapters, transfom){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | transform<int>([](int i){return i * i;});
    int pos = 1;
    for (int i : after){
        ASSERT_EQ(i, pos * pos);
        pos++;
    }
}

TEST(Adapters, filter){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | filter<int>([](int i){return i % 2;});
    int pos = 0;
    for (int i : after){
        ASSERT_EQ(i, 2 * pos + 1);
        pos++;
    }
}

TEST(Adapters, keys){
    std::set<std::pair<std::string, int>> before = {std::make_pair("Moskow", 1), std::make_pair("Saint Petersburg", 2), std::make_pair("Zaragoza", 3), std::make_pair("Munich", 4), std::make_pair("London", 5)};
    auto after = before | keys();
    ASSERT_EQ(*after.begin(), "London");
    ASSERT_EQ(*after.begin()++, "Moskow");
    ASSERT_EQ(*after.end()--, "Zaragoza");
}

TEST(Adapters, values){
    std::set<std::pair<std::string, int>> before = {std::make_pair("Mockow", 1), std::make_pair("Saint Petersburg", 2), std::make_pair("Zaragoza", 3), std::make_pair("Munich", 4), std::make_pair("London", 5)};
    auto after = before | values();
    ASSERT_EQ(*after.begin(), 5);
    ASSERT_EQ(*after.begin()++, 1);
    ASSERT_EQ(*after.end()--, 3);
}

TEST(Adapters, takeAnddrop){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | take(5) | drop(3) ;
    ASSERT_EQ(after[0], 4);
    ASSERT_EQ(after[1], 5);
}

TEST(Adapters, takeDropAndTransform){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | take(5) | drop(3) | transform<int>([](int i){return i * i;});
    ASSERT_EQ(after[0], 16);
    ASSERT_EQ(after[1], 25);
}

TEST(Adapters, takeDropTransformAndReverse){
    std::vector<int> before = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto after = before | reverse() | take(5) | drop(3) | transform<int>([](int i){return i * i;});
    ASSERT_EQ(after[0], 49);
    ASSERT_EQ(after[1], 36);
}

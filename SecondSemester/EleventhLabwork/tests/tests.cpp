//
// Created by sigris on 01.05.2024.
//

#include "gtest/gtest.h"
#include "finder/FinderProcessor.cpp"
#include "indexator/IndexatorProcessor.cpp"
#include "sstream"
#include "fstream"

TEST(SSE, ParserAssert1) {
    int a = 7;
    char *b[7]{"for", "AND", "while", "OR", "vector", "AND", "int"};
    Request now = GetRequest(a, b);
}

TEST(SSE, ParserAssert2){
    int a = 7;
    char* b[7]{"(float", "AND", "string)", "OR", "(std", "AND", "size)"};
    Request now = GetRequest(a, b);
}

TEST(SSE, ParserAssert3){
    int a = 1;
    char* b[1]{"Привет"};
    Request now = GetRequest(a, b);
}

TEST(SSE, ParserAssert4){
    int a = 15;
    char* b[15]{"(while", "OR", "for)", "AND", "vector", "AND", "int", "AND", "(size", "OR", "type)", "AND", "(double", "AND", "float)"};
    Request now = GetRequest(a, b);
}


TEST(SSE, First){
    int a = 5;
    char *b[5]{"/Users/sigris/AllLabs", "/Users/sigris/SecondTest/ans.txt", "Help", "OR", "Hamming"};
    char* c[5]{"/Users/sigris/AllLabs", "/Users/sigris/SecondTest/ans.txt", "(Help", "OR", "Hamming)"};
    Request now1 = GetRequest(a - 2, b +2);
    Request now2 = GetRequest(a - 2, c + 2);
}

TEST(SSE, Second){
    int a = 9;
    char *b[9]{"/Users/sigris/FifthTest", "/Users/sigris/Test/ans.txt", "(bridge", "AND", "town)", "OR", "(father", "AND", "escape)"};
    char* c[9]{"/Users/sigris/FifthTest", "/Users/sigris/Test/ans.txt", "bridge", "AND", "town", "OR", "father", "AND", "escape"};
    Request now1 = GetRequest(a - 2, b + 2);
    Request now2 = GetRequest(a - 2, c + 2);
}

TEST(SSE, Third){
    int a = 9;
    char *b[9]{"/Users/sigris/FifthTest", "/Users/sigris/Test/ans.txt", "(bridge", "AND", "(town", "OR", "father)", "AND", "escape)"};
    char* c[9]{"/Users/sigris/FifthTest", "/Users/sigris/Test/ans.txt", "bridge", "AND", "town", "OR", "father", "AND", "escape"};
    Request now1 = GetRequest(a - 2, b + 2);
    Request now2 = GetRequest(a - 2, c + 2);
}

TEST(SSE, Fourth){
    int a = 5;
    char *b[5]{"/Users/sigris/First", "/Users/sigris/FirstAns.txt", "Help", "OR", "Hamming"};
    char* c[5]{"/Users/sigris/Second", "/Users/sigris/SecondAns.txt", "(Help", "OR", "Hamming)"};
    IndexatorProcess("/Users/sigris/AllLabs", "/Users/sigris/First");
    IndexatorProcess("/Users/sigris/AllLabs", "/Users/sigris/Second");
    FinderProcess(a, b);
    FinderProcess(a, c);
    std::fstream first("/Users/sigris/FirstAns.txt");
    std::string first_comp;
    char cur;
    while (first >> std::noskipws >> cur){
        first_comp += cur;
    }
    std::fstream second("/Users/sigris/SecondAns.txt");
    std::string second_comp;
    while (second >> std::noskipws >> cur){
        second_comp += cur;
    }
    ASSERT_EQ(first_comp, second_comp);
}

TEST(SSE, Fifth){
    int a = 9;
    char *b[9]{"/Users/sigris/Fifth", "/Users/sigris/ans3.txt", "(bridge", "AND", "(town", "OR", "father)", "AND", "escape)"};
    char* c[9]{"/Users/sigris/Fifth", "/Users/sigris/ans4.txt", "bridge", "AND", "town", "OR", "father", "AND", "escape"};
    IndexatorProcess("/Users/sigris/FifthTest", "/Users/sigris/Fifth");
    FinderProcess(a, b);
    FinderProcess(a, c);
    std::fstream first("/Users/sigris/ans3.txt");
    std::string first_comp;
    char cur;
    while (first >> std::noskipws >> cur){
        first_comp += cur;
    }
    std::fstream second("/Users/sigris/ans4.txt");
    std::string second_comp;
    while (second >> std::noskipws >> cur){
        second_comp += cur;
    }
    ASSERT_NE(first_comp, second_comp);
}
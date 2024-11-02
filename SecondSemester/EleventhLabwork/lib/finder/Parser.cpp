//
// Created by sigris on 01.05.2024.
//

#include "iostream"
#include "Parser.h"

const char* kAnd = "AND";
const char* kOr = "OR";

int FindCorrectPositionForRoot(char* argv[], int left_border, int right_border){
    if (argv[right_border][strlen(argv[right_border]) - 1] != ')'){
        if (argv[right_border - 1] == kAnd || argv[right_border - 1] == kOr){
            return right_border - 1;
        } else {
            std::cerr << "Bad request";
            exit(1);
        }
    } else {
        int pos = right_border;
        while (argv[pos][0] != '('){
            pos--;
            if (pos == left_border){
                break;
            }
        }
        pos--;
        if (pos == -1){
            return 1;
        }
        if (argv[pos] == kAnd || argv[pos] == kOr) {
            argv[pos + 1] = argv[pos + 1] + 1;
            size_t len = strlen(argv[right_border]) - 1;
            char temp[] = {0};
            strncpy(temp, argv[right_border], len);
            return pos;
        } else {
            std::cerr << "Bad request";
            exit(1);
        }
    }
}

Request GetRequest(int argc, char* argv[]){
    Request request;
    if (argc == 1){
        request.request_definition.AddNode(nullptr, false, 1, 0);
        request.request_definition.AddValue(request.request_definition.root, false, argv[0], 1);
        request.OccurrenceFrequency.emplace(argv[0], std::vector<IndexInFile>());
    } else {
        ProcessSubRequest(request, 0, argc - 1, argv, nullptr);
    }
    return request;
}

void ProcessSubRequest(Request& request, int left_border, int right_border, char* requests_definitions[], Node* adding_position){
    int root_pos = FindCorrectPositionForRoot(requests_definitions, left_border, right_border);
    if (adding_position == nullptr) {
        request.request_definition.AddNode(adding_position, false, int(requests_definitions[root_pos] == kAnd) + 1, root_pos);
    } else {
        request.request_definition.AddNode(adding_position, root_pos < adding_position->number_in_request, int(requests_definitions[root_pos] == kAnd) + 1, root_pos);
        if (root_pos < adding_position->number_in_request){
            adding_position = adding_position->left_son;
        } else {
            adding_position = adding_position->right_son;
        }
    }
    if (adding_position == nullptr){
        adding_position = request.request_definition.root;
    }
    Node* right_requr = adding_position;
    for (int i = root_pos; i < right_border; i += 2){
        if (requests_definitions[i + 1][0] == '('){
            int t = i + 1;
            while (requests_definitions[t][strlen(requests_definitions[t]) - 1] != ')') {
                t++;
            }
            ProcessSubRequest(request, i + 1, t, requests_definitions, right_requr);
            i = t;
        }
        if (i + 2 <= right_border - 1) {
            request.request_definition.AddNode(right_requr, false, int(requests_definitions[i + 2] == kAnd) + 1, i + 2);
            right_requr = right_requr->right_son;
        }
        if (i + 1 <= right_border) {
            std::string temp;
            temp = requests_definitions[i + 1];
            if (requests_definitions[i + 1][strlen(requests_definitions[i + 1]) - 1] == ')') {
                temp.pop_back();
            }
            request.request_definition.AddValue(right_requr, i + 1 != right_border, temp, i + 1);
            request.OccurrenceFrequency.emplace(temp, std::vector<IndexInFile>());
        }
    }
    Node* left_requr = adding_position;
    for (int i = root_pos; i > left_border; i -= 2){
        if (requests_definitions[i - 1][strlen(requests_definitions[i - 1]) - 1] == ')'){
            int t = i - 1;
            while (requests_definitions[t][0] != '('){
                t--;
            }
            ProcessSubRequest(request, t, i - 1, requests_definitions, left_requr);
            i = t;
        }
        if (i - 2 > left_border - 1) {
            request.request_definition.AddNode(left_requr, true, int(requests_definitions[i - 2] == kAnd) + 1, i - 2);
            left_requr = left_requr->left_son;
        }
        if (i - 1 >= left_border) {
            std::string temp;
            temp = requests_definitions[i - 1];
            if (requests_definitions[i - 1][0] == '(') {
                temp.erase(temp.begin());
            }
            request.request_definition.AddValue(left_requr, true, temp, i - 1);
            request.OccurrenceFrequency.emplace(temp, std::vector<IndexInFile>());
        }
        if (i - 1 == left_border){
            std::string temp;
            temp = requests_definitions[i + 1];
            request.request_definition.size--;
            if (requests_definitions[i + 1][strlen(requests_definitions[i + 1]) - 1] == ')') {
                temp.pop_back();
            }
            request.request_definition.AddValue(left_requr, false, temp, i + 1);
            request.OccurrenceFrequency.emplace(temp, std::vector<IndexInFile>());
        }
    }
}

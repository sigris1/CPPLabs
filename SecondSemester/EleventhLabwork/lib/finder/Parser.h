//
// Created by sigris on 01.05.2024.
//

#pragma once

#include "vector"
#include "Request.h"

Request GetRequest(int argc,char* argv[]);

void ProcessSubRequest(Request& request, int left_border, int right_border, char* requests_definitions[], Node* adding_position);
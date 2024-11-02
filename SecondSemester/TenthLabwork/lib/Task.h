//
// Created by sigris on 19.04.2024.
//

#pragma once
#include "My_any.h"


class Task{
public:
    Task() = default;
    virtual my_any exec(){};
    virtual my_any getvalue(){};
    virtual bool isDone(){};
private:
};


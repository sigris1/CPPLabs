//
// Created by sigris on 15.04.2024.
//

#pragma once

#include "iostream"
#include "UnaryTask.h"
#include "BinaryTask.h"
#include "vector"
#include "My_any.h"

const uint16_t kUnaryTask = 1;
const uint16_t kBinaryTask = 2;

class TTaskScheduler{
public:
    template<class functor, class first>
    unary_task<functor, first> add(functor now, first arg) {
        unary_task<functor, first> now_task(now, arg);
        tasks_.push_back(&now_task);
        return now_task;
    }

    template<class functor, class first, class second>
    binary_task<functor, first, second> add(functor now, first first_argument, second second_argument){
        binary_task<functor, first, second> now_task(now, first_argument, second_argument);
        tasks_.push_back(&now_task);
        return now_task;
    }

    template<class T, class task>
    T getResult(task tas){
        return tas.getvalue().template Getval<T>();
    }

    template<class T, class task>
    auto getFutureResult(task& tas){
        return tas.template getNextValue<T>();
    }

    void executeAll(){
        for (auto i : tasks_){
            if (!i->isDone()) {
                i->exec();
            }
        }
    }
private:
    std::vector<Task*> tasks_;
};

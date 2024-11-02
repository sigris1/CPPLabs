//
// Created by sigris on 18.04.2024.
//

#pragma once
#include "Task.h"

template<class functor, class first>
class unary_task : public Task{
public:
    unary_task() = default;

    unary_task(functor func, first first_argument)
      :  f_(func)
      ,  first_argument_(first_argument)
    {}

    ~unary_task() = default;

    unary_task& operator=(const unary_task& other){
        f_ = other.f_;
        first_argument_ = other.first_argument_;
    };

    my_any exec() override{
        return exec_that_();
    }

    my_any getvalue() override{
        return exec_that_();
    }

    template<class T>
    T getNextValue(){
        return f_(first_argument_);
    }

    bool isDone() override{
        return is_done_;
    };

private:
    functor f_;
    first first_argument_;
    my_any result_ = my_any(f_(first_argument_));
    bool is_done_ = true;
    my_any exec_that_(){
        return result_;
    }
};

template<class functor>
class unary_task<functor, Task> : public Task{
public:
    unary_task() = default;

    unary_task& operator=(const unary_task& other){
        f_ = other.f_;
        first_argument_ = other.first_argument_;
    };

    unary_task(functor func, Task& first_argument)
        : f_(func)
        , first_argument_(first_argument)
    {}

    ~unary_task()= default;

    my_any getvalue() override{
        return exec_that_();
    }

    template<class T>
    T getNextValue(){
        return f_(first_argument_.getvalue().template Getval<T>());
    }

    my_any exec() override{
        return exec_that_();
    }

    bool isDone() override{
        return is_done_;
    };

private:
    functor f_;
    Task& first_argument_;
    my_any result_;
    bool is_done_ = false;
    my_any exec_that_(){
        if (!is_done_) {
            is_done_ = true;
            result_(f_(first_argument_.getvalue()));
        }
        return result_;
    }
};
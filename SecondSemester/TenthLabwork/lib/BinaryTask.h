//
// Created by sigris on 18.04.2024.
//
#pragma once
#include "Task.h"

template<class functor, class first, class second>
class binary_task : public Task{
public:
    binary_task() = default;

    binary_task(functor func, first first_argument, second second_argument)
            : f_(func)
            , first_argument_(first_argument)
            , second_argument_(second_argument)
    {}

    binary_task& operator=(const binary_task& other){
        f_ = other.f_;
        first_argument_ = other.first_argument_;
        second_argument_ = other.second_argument_;
    }

    ~binary_task() = default;

    my_any exec() override{
        return exec_that_();
    }

    my_any getvalue() override{
        return exec_that_();
    }

    template<class T>
    T getNextValue(){
        return f_(first_argument_, second_argument_);
    }

    bool isDone() override{
        return is_done_;
    };


private:
    functor f_;
    first first_argument_;
    second second_argument_;
    my_any result_ = my_any(f_(first_argument_, second_argument_));
    bool is_done_ = true;
    my_any exec_that_(){
        return result_;
    }
};

template<class second, class functor>
class binary_task<Task, second, functor> : public Task{
public:
    binary_task() = default;

    binary_task(functor func, Task& first_argument, second second_argument)
            : f_(func)
            , first_argument_(first_argument)
            , second_argument_(second_argument)
    {}

    binary_task& operator=(const binary_task& other){
        f_ = other.f_;
        first_argument_ = other.first_argument_;
        second_argument_ = other.second_argument_;
        result_ = other.result_;
        is_done_ = other.is_done_;
    }


    ~binary_task() = default;

    my_any exec() override{
        return exec_that_();
    }

    my_any getvalue() override{
        return exec_that_();
    }

    template<class T>
    T getNextValue(){
        return f_(first_argument_.getvalue().template Getval<T>(), second_argument_);
    }

    bool isDone() override{
        return is_done_;
    };

private:
    Task& first_argument_;
    functor f_;
    second second_argument_;
    my_any result_;
    bool is_done_ = false;
    my_any exec_that_(){
        if (!is_done_) {
            is_done_ = true;
            result_(f_(first_argument_.getvalue(), second_argument_));
        }
        return result_;
    }
};

template<class first, class functor>
class binary_task<first, Task, functor> : public Task{
public:
    binary_task() = default;

    binary_task(functor func, first first_argument, Task& second_argument)
            : f_(func)
            , first_argument_(first_argument)
            , second_argument_(second_argument)
    {}

    binary_task& operator=(const binary_task& other){
        f_ = other.f_;
        first_argument_ = other.first_argument_;
        second_argument_ = other.second_argument_;
    }


    ~binary_task() = default;

    my_any exec() override{
        return exec_that_();
    }

    my_any getvalue() override{
        return exec_that_();
    }

    template<class T>
    T getNextValue(){
        return f_(first_argument_, second_argument_.getvalue().template Getval<T>());
    }

    bool isDone() override{
        return is_done_;
    };

private:
    functor f_;
    first first_argument_;
    Task& second_argument_;
    my_any result_;
    bool is_done_ = false;
    my_any exec_that_(){
        if (!is_done_) {
            is_done_ = true;
            result_(f_(first_argument_, second_argument_.getvalue()));
        }
        return result_;
    }
};

template<class functor>
class binary_task<Task, Task, functor> : public Task{
public:
    binary_task() = default;

    binary_task(functor func, Task& first_argument, Task& second_argument)
            : f_(func)
            , first_argument_(first_argument)
            , second_argument_(second_argument)
    {}

    binary_task& operator=(const binary_task& other){
        f_ = other.f_;
        first_argument_ = other.first_argument_;
        second_argument_ = other.second_argument_;
    }

    ~binary_task() = default;

    my_any exec() override{
        return exec_that_();
    }

    my_any getvalue() override{
        return exec_that_();
    }

    template<class T>
    T getNextValue(){
        return f_(first_argument_.getvalue().template Getval<T>(), second_argument_.getvalue().template Getval<T>());
    }

    bool isDone() override{
        return is_done_;
    };

private:
    functor f_;
    Task& first_argument_;
    Task& second_argument_;
    my_any result_;
    bool is_done_ = false;
    my_any exec_that_(){
        if (!is_done_) {
            is_done_ = true;
            result_(f_(first_argument_.getvalue(), second_argument_.getvalue()));
        }
        return result_;
    }
};


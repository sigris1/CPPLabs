//
// Created by sigris on 15.04.2024.
//

#include "gtest/gtest.h"
#include "Scheduler.h"
#include "cmath"

//Квадратное уравнение
TEST(task_scheduler_tests, QuadraticEquation1){
    float a = 2;
    float b = -2;
    float c = 0;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a, float c){return -4 * a * c;}, a, c);
    auto id2 = scheduler.add([](float b, float v){return b * b + v;}, b, scheduler.getFutureResult<float>(id1));
    auto id3 = scheduler.add([](float b, float d){return -b + std::sqrt(d);}, b, scheduler.getFutureResult<float>(id2));
    auto id4 = scheduler.add([](float b, float d){return -b - std::sqrt(d);}, b, scheduler.getFutureResult<float>(id2));
    auto id5 = scheduler.add([](float a, float v){return v/(2*a);}, a, scheduler.getFutureResult<float>(id3));
    auto id6 = scheduler.add([](float a, float v){return v/(2*a);},a, scheduler.getFutureResult<float>(id4));
    scheduler.executeAll();
    ASSERT_EQ(scheduler.getResult<float>(id5), 1);
    ASSERT_EQ(scheduler.getResult<float>(id6), 0);
}

//Квадратное уравнение
TEST(task_scheduler_tests, QuadraticEquation2){
    float a = 1;
    float b = -2;
    float c = 0;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a, float c){return -4 * a * c;}, a, c);
    auto id2 = scheduler.add([](float b, float v){return b * b + v;}, b, scheduler.getFutureResult<float>(id1));
    auto id3 = scheduler.add([](float b, float d){return -b + std::sqrt(d);}, b, scheduler.getFutureResult<float>(id2));
    auto id4 = scheduler.add([](float b, float d){return -b - std::sqrt(d);}, b, scheduler.getFutureResult<float>(id2));
    auto id5 = scheduler.add([](float a, float v){return v/(2*a);}, a, scheduler.getFutureResult<float>(id3));
    auto id6 = scheduler.add([](float a, float v){return v/(2*a);},a, scheduler.getFutureResult<float>(id4));
    scheduler.executeAll();
    ASSERT_EQ(scheduler.getResult<float>(id5), 2);
    ASSERT_EQ(scheduler.getResult<float>(id6), 0);
}

//Вычисление гипотенузы
TEST(task_scheduler_tests, Hypotenuse){
    float a = 3;
    float b = 4;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a){return a * a;}, a);
    auto id2 = scheduler.add([](float b){return b * b;}, b);
    auto id3 = scheduler.add([](float x, float y){return x + y;}, scheduler.getFutureResult<float>(id1), scheduler.getFutureResult<float>(id2));
    auto id4 = scheduler.add([](float x){return sqrt(x);}, scheduler.getFutureResult<float>(id3));
    scheduler.executeAll();
    ASSERT_EQ(scheduler.getResult<float>(id4), 5);
}

//Площадь круга
TEST(task_scheduler_tests, CircleArea){
    float a = 10;
    float pi = 3.14;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a){return a * a;}, a);
    auto id2 = scheduler.add([](float a, float b){return b * a;}, scheduler.getFutureResult<float>(id1), pi);
    scheduler.executeAll();
    ASSERT_EQ(scheduler.getResult<float>(id2), 314);
}

//Сила Ампера
TEST(task_scheduler_tests, AmperePower){
    float B = 11.32;
    float I = 12.23;
    float l = 18.435;
    float a = 2123;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a){return sin(a);}, a);
    auto id2 = scheduler.add([](float a, float b){return a * b;}, B, I);
    auto id3 = scheduler.add([](float a, float b){return a * b;}, scheduler.getFutureResult<float>(id2), l);
    auto id4 = scheduler.add([](float a, float b){return a * b;}, scheduler.getFutureResult<float>(id2), scheduler.getFutureResult<float>(id1));
    scheduler.executeAll();
    ASSERT_EQ(trunc(scheduler.getResult<float>(id4)), -90);
}

//Индуктивность катушки
TEST(task_scheduler_tests, CoilInductance){
    float m0 = 12.2;
    float m = 43.13;
    float n = 3.312;
    float l = 31;
    float s = 0.308;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a, float b){return a * b;}, m0, m);
    auto id2 = scheduler.add([](float a){return a * a;}, n);
    auto id3 = scheduler.add([](float a, float b){return a * b;}, scheduler.getFutureResult<float>(id1), scheduler.getFutureResult<float>(id2));
    auto id4 = scheduler.add([](float a, float b){return a * b;}, scheduler.getFutureResult<float>(id3), l);
    auto id5 = scheduler.add([](float a, float b){return a * b;}, scheduler.getFutureResult<float>(id4), s);
    scheduler.executeAll();
    ASSERT_EQ(trunc(scheduler.getResult<float>(id5)), 55110);
}

// Вычисление выражения ((6.63 + (56.62 + 16.8)) + (-((60.53 + 3.61) + 14.91))) * (20.63 + (-((15.16 + 52.34) + (-52.49))) + 7.38)
TEST(task_scheduler_tests, ExpressionEvaluation){
    float a = 6.63;
    float b = 56.62;
    float c = 16.8;
    float d = 60.53;
    float e = 3.61;
    float f = 14.91;
    float g = 20.63;
    float h = 15.16;
    float i = 52.34;
    float j = -52.49;
    float k = 7.38;
    TTaskScheduler scheduler;
    auto id1 = scheduler.add([](float a, float b){return a + b;}, b, c);
    auto id2 = scheduler.add([](float a, float b){return a + b;}, a, scheduler.getFutureResult<float>(id1));
    auto id3 = scheduler.add([](float a, float b){return a + b;}, d, e);
    auto id4 = scheduler.add([](float a, float b){return a + b;}, scheduler.getFutureResult<float>(id3), f);
    auto id5 = scheduler.add([](float a){return -a;}, scheduler.getFutureResult<float>(id4));
    auto id6 = scheduler.add([](float a, float b){return a + b;}, scheduler.getFutureResult<float>(id2), scheduler.getFutureResult<float>(id5));
    auto id7 = scheduler.add([](float a, float b){return a + b;}, h, i);
    auto id8 = scheduler.add([](float a, float b){return a + b;}, scheduler.getFutureResult<float>(id7), j);
    auto id9 = scheduler.add([](float a){return -a;}, scheduler.getFutureResult<float>(id8));
    auto id10 = scheduler.add([](float a, float b){return a + b;}, scheduler.getFutureResult<float>(id9), k);
    auto id11 = scheduler.add([](float a, float b){return a + b;}, g, scheduler.getFutureResult<float>(id10));
    auto id12 = scheduler.add([](float a, float b){return a * b;}, scheduler.getFutureResult<float>(id6), scheduler.getFutureResult<float>(id11));
    ASSERT_EQ(round(scheduler.getResult<float>(id12)), 13);
}

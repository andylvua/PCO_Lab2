#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"
//
// Created by Andrew Yaroshevych on 06.10.2022.
//
#include "benchmark/benchmark.h"
#include "../library/mystring.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"
static void MyStringCopyConstructor(benchmark::State& state) {
    my_str_t char_n_string(1000000, 'a');
    for (auto _ : state)
        my_str_t copy(char_n_string);
}

static void STDStringCopyConstructor(benchmark::State& state) {
    std::string char_n_string(1000000, 'a');
    for (auto _ : state)
        std::string copy(char_n_string);
}

static void MyStringAssignmentOperator(benchmark::State& state) {
    my_str_t char_n_string(10000, 'a');
    my_str_t copy;
    for (auto _ : state)
        copy = char_n_string;
}

static void STDStringAssignmentOperator(benchmark::State& state) {
    std::string char_n_string(10000, 'a');
    std::string copy;
    for (auto _ : state)
        copy = char_n_string;
}

static void MyStringSubstring(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    for (auto _ : state)
        my_str_t copy = char_n_string.substr(0, 5);
}

static void STDStringSubstring(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    for (auto _ : state)
        std::string copy = char_n_string.substr(0, 5);
}

static void MyStringFind(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.find('a');
}

static void STDStringFind(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.find('a');
}

static void MyStringInsert(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    my_str_t to_insert(100, 'b');
    for (auto _ : state)
        char_n_string.insert(char_n_string.size() - 1, to_insert);
}

static void STDStringInsert(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    std::string to_insert(100, 'b');
    for (auto _ : state)
        char_n_string.insert(char_n_string.size() - 1, to_insert);
}

static void MyStringResize(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.resize(10000);
}

static void STDStringResize(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.resize(10000);
}

static void MyStringErase(benchmark::State& state) {
    for (auto _ : state) {
        my_str_t char_n_string(1000, 'a');
        char_n_string.erase(0, 100);
    }
}

static void STDStringErase(benchmark::State& state) {
    for (auto _ : state) {
        std::string char_n_string(1000, 'a');
        char_n_string.erase(0, 100);
    }
}

static void MyStringAppend(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    my_str_t to_append(100, 'b');
    for (auto _ : state)
        char_n_string.append(to_append);
}

static void STDStringAppend(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    std::string to_append(100, 'b');
    for (auto _ : state)
        char_n_string.append(to_append);
}

static void MyStringConcatenationOperator(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    my_str_t to_insert(100, 'b');
    for (auto _ : state)
        char_n_string += to_insert;
}

static void STDStringConcatenationOperator(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    std::string to_insert(100, 'b');
    for (auto _ : state)
        char_n_string += to_insert;
}

static void MyStringMultiplyOperator(benchmark::State& state) {
    for (auto _ : state) {
        my_str_t char_n_string(100, 'a');
        char_n_string *= 100;
    }
}

static void MyStringReserve(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.reserve(10000);
}

static void STDStringReserve(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.reserve(10000);
}

static void MyStringShrinkToFit(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.shrink_to_fit();
}

static void STDStringShrinkToFit(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.shrink_to_fit();
}

static void MyStringSwap(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    my_str_t to_swap(100, 'b');
    for (auto _ : state)
        char_n_string.swap(to_swap);
}

static void STDStringSwap(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    std::string to_swap(100, 'b');
    for (auto _ : state)
        char_n_string.swap(to_swap);
}

static void MyStringAt(benchmark::State& state) {
    my_str_t char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.at(0);
}

static void STDStringAt(benchmark::State& state) {
    std::string char_n_string(1000, 'a');
    for (auto _ : state)
        char_n_string.at(0);
}

BENCHMARK(MyStringCopyConstructor);
BENCHMARK(STDStringCopyConstructor);
BENCHMARK(MyStringAssignmentOperator);
BENCHMARK(STDStringAssignmentOperator);
BENCHMARK(MyStringSubstring);
BENCHMARK(STDStringSubstring);
BENCHMARK(MyStringFind);
BENCHMARK(STDStringFind);
BENCHMARK(MyStringInsert);
BENCHMARK(STDStringInsert);
BENCHMARK(MyStringResize);
BENCHMARK(STDStringResize);
BENCHMARK(MyStringErase);
BENCHMARK(STDStringErase);
BENCHMARK(MyStringAppend);
BENCHMARK(STDStringAppend);
BENCHMARK(MyStringConcatenationOperator);
BENCHMARK(STDStringConcatenationOperator);
BENCHMARK(MyStringMultiplyOperator);
BENCHMARK(MyStringReserve);
BENCHMARK(STDStringReserve);
BENCHMARK(MyStringShrinkToFit);
BENCHMARK(STDStringShrinkToFit);
BENCHMARK(MyStringSwap);
BENCHMARK(STDStringSwap);
BENCHMARK(MyStringAt);
BENCHMARK(STDStringAt);


BENCHMARK_MAIN();
#pragma clang diagnostic pop
#pragma clang diagnostic pop

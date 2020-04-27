#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);

void PrintStats(std::vector<Person> persons);
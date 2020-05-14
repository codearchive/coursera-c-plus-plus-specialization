#include "element.h"

#include <iostream>
#include <set>

int main() {
    std::set<int> numbers = { 1, 4, 6 };
    std::cout << *FindNearestElement(numbers, 0) << " " <<
                 *FindNearestElement(numbers, 3) << " " <<
                 *FindNearestElement(numbers, 5) << " " <<
                 *FindNearestElement(numbers, 6) << " " <<
                 *FindNearestElement(numbers, 100) << std::endl;

    std::set<int> empty_set;

    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
    return 0;
}
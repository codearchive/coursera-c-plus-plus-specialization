#include "element.h"

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border) {
    const auto lb = numbers.lower_bound(border);
    if (lb == numbers.begin()) {
        return lb;
    }

    const auto prev_lb = prev(lb);
    if (lb == numbers.end()) {
        return prev_lb;
    }

    if (border - *prev_lb <= *lb - border) {
        return prev_lb;
    }

    return lb;
}

//set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
//    if (!numbers.empty()) {
//        if (*numbers.begin() < border and border <= *prev(numbers.end())) {
//            auto right_side_element = numbers.lower_bound(border);
//            auto left_side_element = prev(right_side_element);
//            if (border - *left_side_element <= *right_side_element - border) {
//                return left_side_element;
//            }
//            return right_side_element;
//        }
//        if (border <= *numbers.begin()) {
//            return numbers.begin();
//        }
//        return prev(numbers.end());
//    }
//    return numbers.end();
//}
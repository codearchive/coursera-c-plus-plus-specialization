#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort_2parts(RandomIt range_begin, RandomIt range_end) {
    const size_t container_size = range_end - range_begin;
    if (container_size < 2) {
        return;
    }

    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto it_middle = begin(elements);
    for (size_t i = 0; i < container_size / 2; ++i) {
        ++it_middle;
    }

    MergeSort_2parts(begin(elements), it_middle);
    MergeSort_2parts(it_middle, end(elements));
    merge(begin(elements), it_middle, it_middle, end(elements), range_begin);
}

template <typename RandomIt>
void MergeSort_3parts(RandomIt range_begin, RandomIt range_end) {
    const size_t container_size = range_end - range_begin;
    if (container_size < 2) {
        return;
    }

    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto it_part_1 = begin(elements) + container_size / 3;
    auto it_part_2 = begin(elements) + 2 * container_size / 3;


    MergeSort_3parts(begin(elements), it_part_1);
    MergeSort_3parts(it_part_1, it_part_2);
    MergeSort_3parts(it_part_2, end(elements));
    std::vector<typename RandomIt::value_type> temp;
    merge(begin(elements), it_part_1, it_part_1, it_part_2, back_inserter(temp));
    merge(begin(temp), end(temp), it_part_2, end(elements), range_begin);
}


int main() {
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
    MergeSort_2parts(begin(v), end(v));

    //std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    //MergeSort_3parts(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}

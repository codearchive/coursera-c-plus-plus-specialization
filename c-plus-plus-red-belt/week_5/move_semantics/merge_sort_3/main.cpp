#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    const size_t quantity = range_end - range_begin;
    if (quantity < 2) return;
    vector<typename RandomIt::value_type> pool(make_move_iterator(range_begin),
                                               make_move_iterator(range_end));

    auto it_part_1 = pool.begin() + quantity / 3;
    auto it_part_2 = pool.begin() + 2 * quantity / 3;

    MergeSort(pool.begin(), it_part_1);
    MergeSort(it_part_1, it_part_2);
    MergeSort(it_part_2, pool.end());
    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(pool.begin()), make_move_iterator(it_part_1),
          make_move_iterator(it_part_1), make_move_iterator(it_part_2),
          back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()),
          make_move_iterator(it_part_2), make_move_iterator(pool.end()),
          range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}

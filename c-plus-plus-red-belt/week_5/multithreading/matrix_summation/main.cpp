#include "profile.h"
#include "test_runner.h"

#include <cmath>
#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

template<typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
        : begin_(begin), end_(end)
    {}
    Iterator begin() const { return begin_; }
    Iterator end() const { return end_; }
    size_t size() const { return end_ - begin_; }
private:
    Iterator begin_, end_;
    size_t size_;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        size_t elements = end - begin;
        size_t n_pages = ceil(static_cast<double>(elements) / page_size);
        Iterator it_curr = begin;
        for (size_t i = 0; i < n_pages; ++i) {
            Iterator it_next = next(it_curr, min(elements, page_size));
            pages_.push_back(IteratorRange(it_curr, it_next));
            it_curr = it_next;
            elements -= page_size;
        }
    }
    size_t size() const { return pages_.size(); }
    auto begin() const { return pages_.begin(); }
    auto end() const { return pages_.end(); }
private:
    vector<IteratorRange<Iterator>> pages_;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

template<typename T>
int64_t SumSubMatrix(const T& page) {
    int64_t sum = 0;
    for (const vector<int>& vec : page) {
        sum += static_cast<int64_t>(accumulate(vec.begin(), vec.end(), 0));
    }
    return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t result = 0;
    vector<future<int64_t>> futures;
    size_t page_size = matrix.size() / 4;
    for (const auto& page : Paginate(matrix, page_size < 1 ? 1 : page_size)) {
        futures.push_back(async([=]{ return SumSubMatrix(page); }));
    }

    for (auto& f : futures) {
        result += f.get();
    }
    return result;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    LOG_DURATION("speed test");
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 272);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}

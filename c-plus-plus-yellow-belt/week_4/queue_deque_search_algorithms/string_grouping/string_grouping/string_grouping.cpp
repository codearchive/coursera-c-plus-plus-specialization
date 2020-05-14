#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>


/*
// 1st part
template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix);

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {

    std::string prefix_str(1, prefix);
    auto lb = std::equal_range(range_begin, range_end, prefix_str, [=](const auto& element, const std::string& value) {
        return element[0] < value[0];
    });

    return lb;
}
*/

// 2nd part
template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const std::string& prefix);

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const std::string& prefix) {
    const size_t str_len = prefix.size();
    auto lb = std::equal_range(range_begin, range_end, prefix, [=](const auto& element, const std::string& value) {
        return element.substr(0, str_len) < value.substr(0, str_len);
    });
    return lb;
}

int main() {
    /*
    const std::vector<std::string> sorted_strings = { "moscow", "murmansk", "vologda" };

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    std::cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << std::endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    std::cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << std::endl;
    */

    const std::vector<std::string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << std::endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    std::cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << std::endl;

    return 0;
}

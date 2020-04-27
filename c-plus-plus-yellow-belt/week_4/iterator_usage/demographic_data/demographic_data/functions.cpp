#include "functions.h"

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
    if (range_begin == range_end) {
        return 0;
    }
    std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
    }
    );
    return middle->age;
}

void PrintStats(std::vector<Person> persons) {
    std::cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << std::endl;;

    auto it_gender = partition(begin(persons), end(persons), [](Person p) {
        return p.gender == Gender::FEMALE;
    });
    std::cout << "Median age for females = " << ComputeMedianAge(begin(persons), it_gender) << std::endl;
    std::cout << "Median age for males = " << ComputeMedianAge(it_gender, end(persons)) << std::endl;

    auto it_female_employment = partition(begin(persons), it_gender, [](Person p) {
        return p.gender == Gender::FEMALE && p.is_employed;
    });
    std::cout << "Median age for employed females = " << ComputeMedianAge(begin(persons), it_female_employment) << std::endl;
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(it_female_employment, it_gender) << std::endl;

    auto it_male_employment = partition(it_gender, end(persons), [](Person p) {
        return p.gender == Gender::MALE && p.is_employed;
    });
    std::cout << "Median age for employed males = " << ComputeMedianAge(it_gender, it_male_employment) << std::endl;
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(it_male_employment, end(persons)) << std::endl;
}
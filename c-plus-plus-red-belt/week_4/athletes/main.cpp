#include "profile.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <vector>

template<typename T>
void PrintList(const std::list<T>& list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void RunTest() {
    {
        LOG_DURATION("my solution");
        size_t pair_quantity = 100'000;
        std::list<size_t> athletes_queue;
        std::map<size_t, std::list<size_t>::iterator> athletes_numbers;
        for (size_t i = 0; i < pair_quantity; ++i) {
            size_t athlete = std::rand() % 100'000;
            size_t next_athlete = std::rand() % 100'000;
            if (athletes_numbers.count(athlete)) {
                auto it = athletes_queue.insert(athletes_numbers[athlete], next_athlete);
                athletes_numbers[next_athlete] = it;
            }
            else {
                athletes_queue.push_back(next_athlete);
                athletes_numbers[next_athlete] = prev(athletes_queue.end());
            }
        }
    }
    {
        LOG_DURATION("author's solution");
        const int MAX_ATHLETES = 100'000;
        using Position = list<int>::iterator;

        int n_athletes = MAX_ATHLETES;

        list<int> row;
        vector<Position> athlete_pos(MAX_ATHLETES + 1, row.end());

        for (int i = 0; i < n_athletes; ++i) {
            size_t athlete = std::rand() % 100'000;
            size_t next_athlete = std::rand() % 100'000;
            athlete_pos[athlete] = row.insert(
                        athlete_pos[next_athlete],
                        athlete
                        );
        }
    }
}

int main()
{
    size_t pair_quantity;
    std::cin >> pair_quantity;
    std::list<size_t> athletes_queue;
    std::map<size_t, std::list<size_t>::iterator> athletes_numbers;
    for (size_t i = 0; i < pair_quantity; ++i) {
        size_t athlete, next_athlete;
        std::cin >> next_athlete >> athlete;
        if (athletes_numbers.count(athlete)) {
            auto it = athletes_queue.insert(athletes_numbers[athlete], next_athlete);
            athletes_numbers[next_athlete] = it;
        }
        else {
            athletes_queue.push_back(next_athlete);
            athletes_numbers[next_athlete] = prev(athletes_queue.end());
        }
    }
    PrintList(athletes_queue);
    //RunTest();
    return 0;
}

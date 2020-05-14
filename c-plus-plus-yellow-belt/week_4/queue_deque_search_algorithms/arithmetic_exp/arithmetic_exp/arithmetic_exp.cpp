#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>


int main()
{
    //std::deque<std::string> base;
    //std::string next_symbols;
    //std::cin >> next_symbols;
    //base.push_back(next_symbols);
    //size_t numbers;
    //std::cin >> numbers;
    //std::cin.ignore(1);
    //for (size_t i = 0; i < numbers; i++) {
    //    base.push_front("(");
    //    base.push_back(")");
    //    std::getline(std::cin, next_symbols);
    //    base.push_back(" " + next_symbols);
    //}



    //std::vector<std::string> operation_1{ "+", "-" };
    std::vector<char> operation_2{ '*', '/' };

    std::deque<std::string> base;
    std::string next_symbols;
    std::cin >> next_symbols;
    base.push_back(next_symbols);
    size_t numbers;
    std::cin >> numbers;
    std::cin.ignore(1);
    std::string prev_operation;
    for (size_t i = 0; i < numbers; i++) {
        std::getline(std::cin, next_symbols);
        
        auto r = std::find(operation_2.begin(), operation_2.end(), next_symbols[0]);
        if (r != operation_2.end() && (prev_operation[0] == '+' || prev_operation[0] == '-')) {
            base.push_front("(");
            base.push_back(")");
        }
        base.push_back(" " + next_symbols);
        prev_operation = next_symbols[0];
    }

    std::string result;
    for (const auto& str : base) {
        result += str;
    }
    std::cout << result;
    return 0;
}

#pragma once

#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        size_t newWords = 0;
        for (auto it = words.begin(); it != words.end(); ++it) {
            const auto status = dict.insert(*it);
            if (status.second) { ++newWords; }
        }
        return newWords;
    }

    vector<string> KnownWords() {
        return {dict.begin(), dict.end()};
    }
};

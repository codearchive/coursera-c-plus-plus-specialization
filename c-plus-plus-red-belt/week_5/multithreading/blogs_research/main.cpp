#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <future>
#include <map>
#include <string>
#include <set>
#include <sstream>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (auto other_pair : other.word_frequences) {
            word_frequences[other_pair.first] += other_pair.second;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, stringstream& ss) {
    Stats result;
    string word;
    while (getline(ss, word, ' ')) {
        if (key_words.count(word)) {
            ++result.word_frequences[word];
        }
    }
    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, vector<string>::iterator begin, vector<string>::iterator end) {
    Stats result;
    for (auto it = begin; it != end; ++it) {
        stringstream ss(move(*it));
        result += ExploreLine(key_words, ss);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<string> sentences;
    string line;
    while(getline(input, line)){
        sentences.push_back(move(line));
    }

    int elements = sentences.size();
    size_t number_str_per_thread = 3;
    vector<string>::iterator it_curr = sentences.begin();
    vector<future<Stats>> futures;
    while (elements > 0) {
        vector<string>::iterator it_next = next(it_curr, min(static_cast<size_t>(elements), number_str_per_thread));
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), it_curr, it_next));
        it_curr = it_next;
        elements -= number_str_per_thread;
    }

    Stats result;
    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    {
        LOG_DURATION("test1");
        const auto stats = ExploreKeyWords(key_words, ss);
        const map<string, int> expected = {
            {"yangle", 12},
            {"rocks", 4},
            {"sucks", 2}
        };
        ASSERT_EQUAL(stats.word_frequences, expected);
    }
}

void TestOneString() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 1},
        {"rocks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);

}
int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    RUN_TEST(tr, TestOneString);
}

/*

vector<string> SplitIntoWords(string str) {
    vector<string> result;
    auto str_begin = begin(str);
    const auto str_end = end(str);
    while (true) {
        auto it = find(str_begin , str_end , ' ');
        result.push_back(string(str_begin , it));
        if (it == str_end) {
            break;
        } else {
            str_begin = it + 1;
        }
    }
    return result;
}
*/

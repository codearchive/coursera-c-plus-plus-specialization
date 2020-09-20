#include "test_runner.h"

#include <algorithm>
#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> result(1);
    size_t sentence_counter = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it->IsEndSentencePunctuation() && !next(it)->IsEndSentencePunctuation()) {
            result[sentence_counter++].push_back(move(*it));
            if (next(it) != tokens.end()) {
                result.push_back({});
            }
        }
        else {
            result[sentence_counter].push_back(move(*it));
        }
    }
    return result;
}

struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

void TestSplitting() {
    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
                 vector<Sentence<TestToken>>({
                                                 {{"Split"}, {"into"}, {"sentences"}, {"!"}}
                                             })
                 );

    ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}})),
                 vector<Sentence<TestToken>>({
                                                 {{"Split"}, {"into"}, {"sentences"}}
                                             })
                 );

    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
                vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
                                            })
                );

    ASSERT_EQUAL(
                SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
                vector<Sentence<TestToken>>({
                                                {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                                {{"Without"}, {"copies"}, {".", true}},
                                            })
                );
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}

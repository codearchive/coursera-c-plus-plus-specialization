#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s);

vector<string> SplitIntoWords(const string& s) {
    auto it_1 = begin(s);
    auto it_2 = find(begin(s), end(s), ' ');
    vector<string> result;
    while (true) {
        result.push_back({ it_1, it_2 });
        if (it_2 != end(s)) {
            it_1 = ++it_2;
            it_2 = find(it_2, end(s), ' ');
        }
        else {
            break;
        }
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}

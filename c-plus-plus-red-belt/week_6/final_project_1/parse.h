#pragma once

#include "iterator_range.h"
#include "profile.h"

#include <sstream>
#include <string_view>
#include <vector>

using namespace std;

template <typename Container>
string Join(char c, const Container& cont) {
    //LOG_DURATION("Join");
    ostringstream os;
    for (const auto& item : Head(cont, cont.size() - 1)) {
        os << item << c;
    }
    os << *rbegin(cont);
    return os.str();
}

string_view Strip(string_view s);
vector<string_view> SplitBy(string_view s, char sep);
vector<string_view> SplitIntoWordsView(string_view str);

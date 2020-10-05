#include "parse.h"

string_view Strip(string_view s) {
    //LOG_DURATION("Strip")
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && isspace(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

vector<string_view> SplitBy(string_view s, char sep) {
    //LOG_DURATION("SplitBy")
    vector<string_view> result;
    while (!s.empty()) {
        size_t pos = s.find(sep);
        result.push_back(s.substr(0, pos));
        s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
    }
    return result;
}

vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;
    while(true) {
        while(!str.empty() && isspace(str.front())) {
            str.remove_prefix(1);
        }
        if (str.empty()) break;
        size_t space = str.find(' ');
        auto substr = str.substr(0, space);
        result.push_back(substr);
        str.remove_prefix(space != str.npos ? space + 1 : str.size());
    }
    return result;
}

#include "stats.h"

void Stats::AddMethod(std::string_view method) {
    if (!method_stats_.count(method)) {
        ++method_stats_["UNKNOWN"];
    }
    else {
        ++method_stats_[method];
    }
}

void Stats::AddUri(std::string_view uri) {
    if (!uri_stats_.count(uri)) {
        ++uri_stats_["unknown"];
    }
    else {
        ++uri_stats_[uri];
    }
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const {
    return method_stats_;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const {
    return uri_stats_;
}

std::vector<std::string_view> SplitIntoWordsView(std::string_view str) {
    std::vector<std::string_view> result;
    while(true) {
        size_t space = str.find(' ');
        result.push_back(str.substr(0, space));
        if (space == str.npos) {
            break;
        } else {
            str.remove_prefix(space + 1);
        }
    }
    return result;
}

HttpRequest ParseRequest(std::string_view line) {
    HttpRequest http_request;
    size_t begin = line.find_first_not_of(' ');
    std::vector<std::string_view> request_parts = SplitIntoWordsView(line.substr(begin, line.npos));
    http_request.method = request_parts[0];
    http_request.uri = request_parts[1];
    http_request.protocol = request_parts[2];
    return http_request;
}

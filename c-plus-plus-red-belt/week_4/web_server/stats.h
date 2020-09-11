#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <set>
#include <vector>

class Stats {
public:
    void AddMethod(std::string_view method);
    void AddUri(std::string_view uri);
    const std::map<std::string_view, int>& GetMethodStats() const;
    const std::map<std::string_view, int>& GetUriStats() const;
private:
    std::map<std::string_view, int> method_stats_{{"GET",0}, {"PUT",0}, {"POST",0}, {"DELETE",0}, {"UNKNOWN", 0}};
    std::map<std::string_view, int> uri_stats_{{"/",0}, {"/order",0}, {"/product",0}, {"/basket",0}, {"/help", 0}, {"unknown",0}};
};

std::vector<std::string_view> SplitIntoWordsView(std::string_view str);
HttpRequest ParseRequest(std::string_view line);

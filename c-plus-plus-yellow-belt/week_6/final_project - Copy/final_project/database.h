#pragma once

#include "date.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <tuple>
#include <algorithm>
#include <set>
#include <sstream>


class Database {
public:
    void Add(const Date& date, const std::string& event);
    void Print(std::ostream& stream) const;
    template <typename PredFunc>
    int RemoveIf(PredFunc& func) {
        int counter = 0;
        for (auto it_map = database_.begin(); it_map != database_.end(); ++it_map) {
            const Date date = it_map->first;
            auto it_remove = std::stable_partition(it_map->second.begin(), it_map->second.end(), [date, func](const auto& event) {
                return !func(date, event);
            });
            counter += it_map->second.end() - it_remove;
            database_[date].erase(it_remove, it_map->second.end());
        }
        return counter;
    }
    template <typename PredFunc>
    std::map<Date, std::vector<std::string>> FindIf(PredFunc& func) {
        std::map<Date, std::vector<std::string>> entries;
        for (auto it_map = database_.begin(); it_map != database_.end(); ++it_map) {
            const Date date = it_map->first;
            auto it_remove = std::stable_partition(it_map->second.begin(), it_map->second.end(), [date, func](const auto& event) {
                return !func(date, event);
            });
            std::copy(it_remove, it_map->second.end(), std::back_inserter(entries[date]));
        }
        return entries;
    }
    std::string Last(const Date& date) {
        std::stringstream ss;
        const auto lb = database_.lower_bound(date);
        if (lb == database_.begin() && lb->first != date) {
            return "No entries";
        }

        const auto prev_lb = prev(lb);
        ss << prev_lb->first << ' ' << prev_lb->second.back();
        return ss.str();
    }
private:
    std::map<Date, std::vector<std::string>> database_;
    std::map<Date, std::set<std::string>> added_events_;
};

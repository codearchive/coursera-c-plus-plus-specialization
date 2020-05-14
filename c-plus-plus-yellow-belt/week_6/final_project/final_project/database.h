#pragma once

#include "date.h"
#include "entry.h"

#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <sstream>
#include <vector>


using namespace std;

class Database {
public:
    void Add(const Date& date, const std::string& event);
    void Print(std::ostream& stream) const;

    template <typename PredFunc>
    int RemoveIf(PredFunc func) {
        int counter = 0;
        std::set<Date> empty_dates;
        for (auto it_map = database_.begin(); it_map != database_.end(); ++it_map) {
            auto predicate = [it_map, func](const auto& event) {
                return !func(it_map->first, event);
            };
            auto it_border = std::stable_partition(it_map->second.begin(),
                it_map->second.end(),
                predicate);
            for (auto it_remove_set = it_border; it_remove_set != it_map->second.end(); ++it_remove_set) {
                counter += added_events_[it_map->first].erase(*it_remove_set);
            }
            database_[it_map->first].erase(it_border, it_map->second.end());
            if (database_[it_map->first].size() == 0) {
                empty_dates.insert(it_map->first);
            }
        }
        for (auto it_empty_date = empty_dates.begin(); it_empty_date != empty_dates.end(); ++it_empty_date) {
            database_.erase(*it_empty_date);
            added_events_.erase(*it_empty_date);
        }
        return counter;
    }

    template <typename PredFunc>
    std::vector<Entry> FindIf(PredFunc func) const {
        std::vector<Entry> entries;
        for (auto it_map = database_.begin(); it_map != database_.end(); ++it_map) {
            for (auto it_event = it_map->second.begin(); it_event != it_map->second.end(); ++it_event) {
                if (func(it_map->first, *it_event)) {
                    entries.push_back({ it_map->first, *it_event });
                }
            }
        }
        return entries;
    }
    Entry Last(const Date& date) const;
private:
    std::map<Date, std::vector<std::string>> database_;
    std::map<Date, std::set<std::string>> added_events_;
};

#include "database.h"

void Database::Add(const Date& date, const std::string& event) {
    const auto status = added_events_[date].insert(event);
    if (status.second) {
        database_[date].push_back(event);
    }
}

void Database::Print(std::ostream& stream) const {
    for (const auto&[key, value] : database_) {
        for (const auto& event : value) {
            stream << key << ' ' << event << std::endl;
        }
    }
}

Entry Database::Last(const Date& date) const {
    if (database_.empty()) { throw invalid_argument("No entries"); }
    const auto it = database_.upper_bound(date);
    if (it == database_.begin() && date < it->first) {
        throw invalid_argument("No entries");
    }
    const auto prev_it = prev(it);
    return { prev_it->first, prev_it->second.back() };
}
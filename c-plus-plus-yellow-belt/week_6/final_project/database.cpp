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

std::string Database::Last(const Date& date) const {
    if (database_.empty()) { throw invalid_argument("No entries"); }
    const auto up = database_.upper_bound(date);
    std::stringstream ss;
    if (up == database_.begin() && date < up->first) {
        throw invalid_argument("No entries");
    }
    const auto prev_lb = prev(up);
    ss << prev_lb->first << ' ' << prev_lb->second.back();
    return ss.str();
}
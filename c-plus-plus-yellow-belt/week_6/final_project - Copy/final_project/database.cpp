#include "database.h"


void Database::Add(const Date& date, const std::string& event) {
    const auto status = added_events_[date].insert(event);
    if (status.second) {
        database_[date].push_back(event);
    }
}


void Database::Print(std::ostream& stream) const {
    for (const auto& [key, value] : database_) {
        for (const auto& event : value) {
            stream << key << ' ' << event << std::endl;
        }
    }
}


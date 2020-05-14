#include "entry.h"

std::ostream& operator<<(std::ostream& os, const Entry& entry) {
    return os << entry.date << ' ' << entry.event;
}

bool operator==(const Entry& entry, const std::string str) {
    std::stringstream ss;
    ss << entry;
    return ss.str() == str;
}

bool operator!=(const Entry& entry, const std::string str) {
    return !(entry == str);
}
#include "date.h"

Date::Date(const int& year, const int& month, const int& day)
    : year_(year), month_(month), day_(day) 
{}

Date ParseDate(std::istream& is) {
    int year = 0;
    int month = 0;
    int day = 0;
    is >> year;
    is.ignore(1);
    is >> month;
    is.ignore(1);
    is >> day;
    return Date(year, month, day);
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear() << '-'
        << std::setw(2) << std::setfill('0') << date.GetMonth() << '-'
        << std::setw(2) << std::setfill('0') << date.GetDay();
    return stream;
};

bool operator<(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator>(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) > std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) == std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) != std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return lhs > rhs || lhs == rhs;
}
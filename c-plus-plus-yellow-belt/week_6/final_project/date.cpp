#include "date.h"

Date::Date() : year_(0), month_(0), day_(0) {}

Date::Date(const int& year, const int& month, const int& day) {
    if (month < 1 || month > 12) {
        std::string error = "Month value is invalid: " + std::to_string(month);
        throw std::invalid_argument(error);
    }
    if (day < 1 || day > 31) {
        std::string error = "Day value is invalid: " + std::to_string(day);
        throw std::invalid_argument(error);
    }
    year_ = year;
    month_ = month;
    day_ = day;
}

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

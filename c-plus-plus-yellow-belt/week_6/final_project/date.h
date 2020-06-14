#pragma once
#include <string>
#include <iomanip>
//#include <iostream>
#include <algorithm>

using namespace std;

class Date {
public:
    Date();
    Date(const int& year, const int& month, const int& day);
    int GetYear() const { return year_; }
    int GetMonth() const { return month_; }
    int GetDay() const { return day_; }
private:
    int year_;
    int month_;
    int day_;
};

Date ParseDate(std::istream& is);

inline std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.GetYear() << '-'
        << std::setw(2) << std::setfill('0') << date.GetMonth() << '-'
        << std::setw(2) << std::setfill('0') << date.GetDay();
    return stream;
};

inline bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() != rhs.GetYear())
    {
        return lhs.GetYear() < rhs.GetYear();
    }
    if (lhs.GetMonth() != rhs.GetMonth())
    {
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetDay() < rhs.GetDay();
}

inline bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() != rhs.GetYear())
    {
        return lhs.GetYear() > rhs.GetYear();
    }
    if (lhs.GetMonth() != rhs.GetMonth())
    {
        return lhs.GetMonth() > rhs.GetMonth();
    }
    return lhs.GetDay() > rhs.GetDay();
}

inline bool operator==(const Date& lhs, const Date& rhs) {
    return (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay());
}

inline bool operator!=(const Date& lhs, const Date& rhs) {
    return (lhs.GetYear() != rhs.GetYear() || lhs.GetMonth() != rhs.GetMonth() || lhs.GetDay() != rhs.GetDay());
}
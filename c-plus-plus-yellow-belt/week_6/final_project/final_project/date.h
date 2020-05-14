#pragma once
#include <algorithm>
#include <iomanip>
#include <string>
#include <tuple>

class Date {
public:
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

std::ostream& operator<<(std::ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

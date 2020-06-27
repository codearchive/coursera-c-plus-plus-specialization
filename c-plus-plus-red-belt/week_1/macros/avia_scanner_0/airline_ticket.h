#pragma once

#include <string>
#include <tuple>
#include <iomanip>
#include <ostream>

using namespace std;

struct Date {
  int year, month, day;
};

struct Time {
  int hours, minutes;
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;


};

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) <
            std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) ==
            std::tie(rhs.year, rhs.month, rhs.day);
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.year << '-'
            << std::setw(2) << std::setfill('0') << date.month << '-'
            << std::setw(2) << std::setfill('0') << date.day;
        return stream;
}

bool operator<(const Time& lhs, const Time& rhs) {
    return std::tie(lhs.hours, lhs.minutes) <
            std::tie(rhs.hours, rhs.minutes);
}

std::ostream& operator<<(std::ostream& stream, const Time& time) {
    stream << std::setw(2) << std::setfill('0') << time.hours << ':'
            << std::setw(2) << std::setfill('0') << time.minutes;
        return stream;
}

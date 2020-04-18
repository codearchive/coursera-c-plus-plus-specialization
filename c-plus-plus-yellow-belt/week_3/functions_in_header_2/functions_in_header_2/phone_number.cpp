#include "phone_number.h"
#include <sstream>

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
    stringstream ss(international_number);
    if (ss.peek() != '+') {
        throw invalid_argument("the number does not start with a '+'");
    }
    ss.ignore(1);
    getline(ss, country_code_, '-');
    getline(ss, city_code_, '-');
    getline(ss, local_number_);
    if (country_code_.size() > 3 || country_code_.empty() || city_code_.size() > 3 || city_code_.empty() || local_number_.empty()) {
        throw invalid_argument("some parts of number are incorrect");
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}

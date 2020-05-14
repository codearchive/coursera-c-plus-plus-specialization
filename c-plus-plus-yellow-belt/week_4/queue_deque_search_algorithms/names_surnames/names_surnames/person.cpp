#include "person.h"

void Person::ChangeFirstName(int year, const std::string& first_name) {
    first_name_history[year] = first_name;
}

void Person::ChangeLastName(int year, const std::string& last_name) {
    last_name_history[year] = last_name;
}

std::string Person::GetFullName(int year) {
    const auto first_name_it = first_name_history.upper_bound(year);
    const auto last_name_it = last_name_history.upper_bound(year);

    if (first_name_it == first_name_history.begin() &&
        last_name_it == last_name_history.begin()) {
        return "Incognito";
    }
    if (first_name_it == first_name_history.begin() &&
        last_name_it != last_name_history.begin()) {
        return prev(last_name_it)->second + " with unknown first name";
    }
    if (first_name_it != first_name_history.begin() &&
        last_name_it == last_name_history.begin()) {
        return prev(first_name_it)->second + " with unknown last name";
    }
    return prev(first_name_it)->second + " " + prev(last_name_it)->second;
}

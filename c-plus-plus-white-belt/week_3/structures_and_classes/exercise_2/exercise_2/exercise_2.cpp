#include <iostream>
#include <string>
#include <map>
//#include "Person.hpp"

using namespace std;

std::string FindNameByYear(const std::map<int, std::string>& names_history, int& year)
{
    std::string result_name;
    for (const auto& name : names_history)
    {
        if (name.first <= year)
        {
            result_name = name.second;
        }
        else
        {
            break;
        }
    }
    return result_name;
}

class Person {
public:
    void ChangeFirstName(int year, const std::string& first_name)
    {
        first_name_history[year] = first_name;
    }
    void ChangeLastName(int year, const std::string& last_name)
    {
        last_name_history[year] = last_name;
    }

    std::string GetFullName(int year)
    {
        std::string first_name = FindNameByYear(first_name_history, year);
        std::string last_name = FindNameByYear(last_name_history, year);

        if (first_name.empty() && last_name.empty())
        {
            return "Incognito";
        }
        if (first_name.empty() && !last_name.empty())
        {
            return last_name + " with unknown first name";
        }
        if (!first_name.empty() && last_name.empty())
        {
            return first_name + " with unknown last name";
        }

        return first_name + " " + last_name;
    }
private:
    std::map<int, std::string> first_name_history;
    std::map<int, std::string> last_name_history;
};




int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}

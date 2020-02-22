#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

string FindNameByYear(const map<int, string>& names_history, int& year)
{
    string result_name;
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

vector<string> FindNameByYearWithHistory(const map<int, string>& names_history, int& year)
{
    vector<string> result_names;
    string prev_name = "";
    for (const auto& name : names_history)
    {
        if (name.first <= year)
        {
            if (prev_name != name.second)
            {
                prev_name = name.second;
                result_names.push_back(name.second);
            }
        }
        else
        {
            break;
        }
    }
    return result_names;
}

string ReturnReverseSet(vector<string>& vec_names)
{
    string result = vec_names[vec_names.size() - 1];
    if (vec_names.size() > 1)
    {
        result += " (";
        for (int i = vec_names.size() - 2; i >= 0; --i)
        {
            result += vec_names[i];
            if (i != 0)
            {
                result += ", ";
            }
        }
        result += ")";
    }
    return result;
}


class Person {
public:
    void ChangeFirstName(int year, const string& first_name)
    {
        first_name_history[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name)
    {
        last_name_history[year] = last_name;
    }

    string GetFullNameWithHistory(int year)
    {
        vector<string> history_first_name_set = FindNameByYearWithHistory(first_name_history, year);
        vector<string> history_last_name_set = FindNameByYearWithHistory(last_name_history, year);;

        int size_first_names = history_first_name_set.size();
        int size_last_names = history_last_name_set.size();

        if (size_first_names == 0 && size_last_names == 0)
        {
            return "Incognito";
        }
        if (size_first_names == 0 && size_last_names > 0)
        {
            return ReturnReverseSet(history_last_name_set) + " with unknown first name";
        }
        if (size_first_names > 0 && size_last_names == 0)
        {
            return ReturnReverseSet(history_first_name_set) + " with unknown last name";
        }

        return ReturnReverseSet(history_first_name_set) + " " + ReturnReverseSet(history_last_name_set);
    }

    string GetFullName(int year)
    {
        string first_name = FindNameByYear(first_name_history, year);
        string last_name = FindNameByYear(last_name_history, year);

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
    map<int, string> first_name_history;
    map<int, string> last_name_history;
};



int main() {
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
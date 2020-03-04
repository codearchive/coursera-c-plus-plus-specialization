#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Name
{
    explicit Name(const string& new_value) : value(new_value) {}
    string value;
};

struct Surname
{
    explicit Surname(const string& new_value) : value(new_value) {}
    string value;
};

struct Day
{
    explicit Day(const int& new_value) : value(new_value) {}
    int value;
};

struct Month
{
    explicit Month(const int& new_value) : value(new_value) {}
    int value;
};

struct Year
{
    explicit Year(const int& new_value) : value(new_value) {}
    int value;
};

struct Student
{
    Student(const Name& new_name,
        const Surname& new_surname,
        const Day& new_day,
        const Month& new_month,
        const Year& new_year) :
        name(new_name.value),
        surname(new_surname.value),
        day(new_day.value),
        month(new_month.value),
        year(new_year.value)
    {}

    string name;
    string surname;
    int day;
    int month;
    int year;
};

int main()
{
    vector<Student> students;
    int number_of_lines;
    cin >> number_of_lines;
    for (int i = 0; i < number_of_lines; ++i)
    {
        string current_name;
        string current_surname;
        int current_day;
        int current_month;
        int current_year;
        cin >> current_name >> current_surname >> current_day >> current_month >> current_year;
        students.push_back({ Name(current_name),
                                 Surname(current_surname),
                                 Day(current_day),
                                 Month(current_month),
                                 Year(current_year) });
    }
    int number_of_queries;
    cin >> number_of_queries;
    for (int i = 0; i < number_of_queries; ++i)
    {
        string query;
        int student_number;
        cin >> query >> student_number;
        if (query == "name" && student_number > 0 && student_number <= students.size())
        {
            cout << students[student_number - 1].name << ' ' << students[student_number - 1].surname << endl;
            continue;
        }
        if (query == "date" && student_number > 0 && student_number <= students.size())
        {
            cout << students[student_number - 1].day << '.' << students[student_number - 1].month << '.' << students[student_number - 1].year << endl;
            continue;
        }

        cout << "bad request" << endl;
    }
    return 0;
}
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
    Date()
    {
        year_ = 0;
        month_ = 0;
        day_ = 0;
    }
    Date(const int& new_year, const int& new_month, const int& new_day)
    {
        if (new_month < 1 || new_month > 12)
        {
            string error = "Month value is invalid: " + to_string(new_month);
            throw invalid_argument(error);
        }
        if (new_day < 1 || new_day > 31)
        {
            string error = "Day value is invalid: " + to_string(new_day);
            throw invalid_argument(error);
        }
        year_ = new_year;
        month_ = new_month;
        day_ = new_day;
    }
    int GetYear() const
    {
        return year_;
    }
    int GetMonth() const
    {
        return month_;
    }
    int GetDay() const
    {
        return day_;
    }
private:
    int year_;
    int month_;
    int day_;
};

Date ParseDate(const string& new_date)
{
    stringstream ss(new_date);

    int year, month, day;
    string end_of_date;
    if (ss >> year && ss.peek() == '-' && ss.ignore(1) && ss >> month && ss.peek() == '-' && ss.ignore(1) && ss >> day && !(ss >> end_of_date))
    {
        return Date(year, month, day);
    }
    string error = "Wrong date format: " + new_date;
    throw invalid_argument(error);
}

ostream& operator<<(ostream& stream, const Date& date)
{
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
        << setw(2) << setfill('0') << date.GetMonth() << '-'
        << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs)
{
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

class Database {
public:
    void AddEvent(const Date& date, const string& event)
    {
        storage_[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {
        set<string>::iterator it;
        for (it = storage_[date].begin(); it != storage_[date].end(); ++it)
        {
            if (*it == event)
            {
                break;
            }
        }
        if (it != storage_[date].end())
        {
            storage_[date].erase(event);
            return true;
        }
        else
        {
            return false;
        }
    }
    int DeleteDate(const Date& date)
    {
        if (!storage_[date].empty())
        {
            int events_counter = storage_[date].size();
            storage_.erase(date);
            return events_counter;
        }
        else
        {
            return 0;
        }
    }

    set<string> Find(const Date& date) const
    {
        set<string> result;
        if (storage_.count(date) > 0)
        {
            result = storage_.at(date);
        }
        return result;
    }

    void Print() const
    {
        for (const auto& record : storage_)
        {
            for (auto curr_event : record.second)
            {
                if (record.first.GetYear() >= 0)
                {
                    cout << record.first << ' ' << curr_event << endl;
                }
            }
        }
    }
private:
    map<Date, set<string>> storage_;
};

int main()
{
    try
    {
        Database db;

        string command_line;
        while (getline(cin, command_line))
        {
            if (command_line.empty()) continue;
            stringstream ss(command_line);
            string new_command_key, new_date, new_event;
            ss >> new_command_key >> new_date >> new_event;
            Date date;
            if (!new_date.empty())
            {
                date = ParseDate(new_date);
            }
            if (new_command_key == "Add")
            {
                db.AddEvent(date, new_event);
            }
            else if (new_command_key == "Del")
            {
                if (!new_event.empty())
                {
                    if (db.DeleteEvent(date, new_event))
                    {
                        cout << "Deleted successfully" << endl;
                    }
                    else
                    {
                        cout << "Event not found" << endl;
                    }
                }
                else
                {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                }
            }
            else if (new_command_key == "Print")
            {
                db.Print();
            }
            else if (new_command_key == "Find")
            {
                const set<string> events = db.Find(date);
                for (const auto& next_event : events)
                {
                    cout << next_event << endl;
                }
            }
            else
            {
                cout << "Unknown command: " << new_command_key << endl;
            }
        }
    }
    catch (const exception& ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
string GetStringException(const T& t, const U& u, const string& hint, string sign) {
    ostringstream os;
    os << "Assertion failed: " << t << " " << sign << " " << u;
    if (!hint.empty()) {
        os << " hint: " << hint;
    }
    return os.str();
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        throw runtime_error(GetStringException(t, u, hint, "!="));
    }
}

template<class T, class U>
void AssertNotEqual(const T& t, const U& u, const string& hint = {}) {
    if (t == u) {
        throw runtime_error(GetStringException(t, u, hint, "=="));
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};


string FindNameByYear(const std::map<int, std::string>& names_history, int& year) {
    std::string result_name;
    for (const auto& name : names_history) {
        if (name.first <= year) {
            result_name = name.second;
        } else {
            break;
        }
    }
    return result_name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_name_history[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_name_history[year] = last_name;
    }
    string GetFullName(int year) {
        string first_name = FindNameByYear(first_name_history, year);
        string last_name = FindNameByYear(last_name_history, year);

        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        }
        if (first_name.empty() && !last_name.empty()) {
            return last_name + " with unknown first name";
        }
        if (!first_name.empty() && last_name.empty()) {
            return first_name + " with unknown last name";
        }
        return first_name + " " + last_name;
    }
private:
    map<int, string> first_name_history;
    map<int, string> last_name_history;
};

void TestChangeFirstName() {
    {
        Person p;
        p.ChangeFirstName(1991, "John");
        AssertEqual(p.GetFullName(1991), "John with unknown last name");
    }
}

void TestChangeLastName() {
    {
        Person p;
        p.ChangeLastName(1992, "Smith");
        AssertEqual(p.GetFullName(1992), "Smith with unknown first name");
    }
}

void TestNoChanges() {
    {
        Person p;
        AssertEqual(p.GetFullName(1993), "Incognito");
    }
}

void TestGetFullName() {
    {
        Person p;
        p.ChangeFirstName(1994, "John");
        p.ChangeLastName(1995, "Smith");
        AssertNotEqual(p.GetFullName(1993), "John Smith");
        AssertEqual(p.GetFullName(1997), "John Smith");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestChangeFirstName, "TestChangeFirstName");
    runner.RunTest(TestChangeLastName, "TestChangeLastName");
    runner.RunTest(TestNoChanges, "TestNoChanges");
    runner.RunTest(TestGetFullName, "TestGetFullName");
    return 0;
}

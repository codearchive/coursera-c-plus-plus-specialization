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
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

template<class T, class U>
void AssertNotEqual(const T& t, const U& u, const string& hint = {}) {
    if (t == u) {
        ostringstream os;
        os << "Assertion failed: " << t << " == " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
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

int GetDistinctRealRootCount(double a, double b, double c) {
    // Quadratic equation solution
    return 0;
}

void TestRootCount() {
    {
        AssertEqual(GetDistinctRealRootCount(16.0, 8.0, 1.0), 1, "a = 16, b = 8, c = 1 -> D = 0");
        AssertEqual(GetDistinctRealRootCount(1.0, 1.0, 1.0), 0, "a = 1, b = 1, c = 1 -> D < 0");
        AssertEqual(GetDistinctRealRootCount(2.0, 5.0, -7.0), 2, "a = 2, b = 5, c = -7 -> D > 0");
        AssertEqual(GetDistinctRealRootCount(0.0, 1.0, 1.0), 1, "a = 0, b = 1, c = 1 -> bx + c = 0");
        AssertEqual(GetDistinctRealRootCount(4.0, 0.0, -1.0), 2, "a = 4, b = 0, c = -1 -> ax^2 + c = 0");
        AssertNotEqual(GetDistinctRealRootCount(0.0, 0.0, 1.0), 1, "a = 0, b = 0, c = 1 -> c = 0");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestRootCount, "TestRootCount");
    return 0;
}

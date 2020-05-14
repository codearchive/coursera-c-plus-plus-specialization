#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os;
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

inline void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}



class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        }
        catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        }
        catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

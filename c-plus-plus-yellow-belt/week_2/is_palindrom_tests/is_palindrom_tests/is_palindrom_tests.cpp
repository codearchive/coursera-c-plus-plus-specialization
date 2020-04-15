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

bool IsPalindrom(string s) {
    for (size_t i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestEmptyString() {
    AssertEqual(IsPalindrom(""), true);
    AssertEqual(IsPalindrom("  "), true);
}

void TestSingleCharacter() {
    AssertEqual(IsPalindrom("a"), true);
    AssertEqual(IsPalindrom("W"), true);
    AssertEqual(IsPalindrom("2"), true);
}

void TestStringWithWhiteSpaces() {
    AssertEqual(IsPalindrom(" aba aba "), true);
    AssertEqual(IsPalindrom(" a a a "), true);
    AssertEqual(IsPalindrom("1e#%#e1"), true);
    AssertNotEqual(IsPalindrom("1a 1 a"), true);
    AssertEqual(IsPalindrom("LeVeL"), true);
}

void TestRegularString() {
    AssertEqual(IsPalindrom("level"), true);
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), true);
    AssertNotEqual(IsPalindrom("level\n"), true);
}

void TestUppercaseLetter() {
    AssertNotEqual(IsPalindrom("lEvel"), true);
    AssertNotEqual(IsPalindrom("wAsitacaroracatisaw"), true);
    AssertNotEqual(IsPalindrom("ABCcba"), true);
}

void TestLoseLetter() {
    AssertNotEqual(IsPalindrom("deve"), true);
    AssertNotEqual(IsPalindrom(" eved"), true);
}

void TestFalseMiddle() {
    AssertNotEqual(IsPalindrom("abcbaa"), true);
    AssertNotEqual(IsPalindrom("aabcba"), true);
}


int main() {
    TestRunner runner;
    runner.RunTest(TestEmptyString, "TestEmptyString");
    runner.RunTest(TestSingleCharacter, "TestSingleCharacter");
    runner.RunTest(TestStringWithWhiteSpaces, "TestStringWithWhiteSpaces");
    runner.RunTest(TestRegularString, "TestRegularString");
    runner.RunTest(TestUppercaseLetter, "TestUppercaseLetter");
    runner.RunTest(TestLoseLetter, "TestLoseLetter");
    runner.RunTest(TestFalseMiddle, "TestFalseMiddle");
    return 0;
}

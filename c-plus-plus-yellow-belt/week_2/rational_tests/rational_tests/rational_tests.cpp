#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

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


class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Invalid argument");
        }
        if (numerator == 0)
        {
            this->numerator = 0;
            this->denominator = 1;
        }
        else if (denominator < 0)
        {
            this->numerator = numerator * -1;
            this->denominator = denominator * -1;
        }
        else
        {
            this->numerator = numerator;
            this->denominator = denominator;
        }

        int tmp_gcd = gcd(this->numerator, this->denominator);
        this->numerator /= tmp_gcd;
        this->denominator /= tmp_gcd;
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

bool operator==(const Rational& num1, const Rational& num2)
{
    return num1.Numerator() == num2.Numerator() && num1.Denominator() == num2.Denominator();
}

Rational operator+(const Rational& num1, const Rational& num2)
{
    int new_numerator = num1.Numerator() * num2.Denominator() + num2.Numerator() * num1.Denominator();
    int new_denominator = num1.Denominator() * num2.Denominator();
    return Rational(new_numerator, new_denominator);
}

Rational operator-(const Rational& num1, const Rational& num2)
{
    int new_numerator = num1.Numerator() * num2.Denominator() - num2.Numerator() * num1.Denominator();
    int new_denominator = num1.Denominator() * num2.Denominator();
    return Rational(new_numerator, new_denominator);
}

Rational operator*(const Rational& num1, const Rational& num2)
{

    int new_numerator = num1.Numerator() * num2.Numerator();
    int new_denominator = num1.Denominator() * num2.Denominator();
    return Rational(new_numerator, new_denominator);
}

Rational operator/(const Rational& num1, const Rational& num2)
{
    if (num2.Numerator() == 0)
    {
        throw domain_error("Division by zero");
    }
    int new_numerator = num1.Numerator() * num2.Denominator();
    int new_denominator = num1.Denominator() * num2.Numerator();
    return Rational(new_numerator, new_denominator);
}

ostream& operator<<(ostream& stream, const Rational& number)
{
    stream << number.Numerator() << "/" << number.Denominator();
    return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
}

istream& operator>>(istream& stream, Rational& number)
{
    if (stream.tellg() == -1) return stream;

    int new_numerator = 0;
    int new_denominator = 1;
    char new_delim;
    stream >> new_numerator >> new_delim >> new_denominator;
    if (new_delim == '/')
    {
        number = Rational(new_numerator, new_denominator);
    }
    else
    {
        throw invalid_argument("Invalid argument");
    }
    return stream;
}

void TestDefaultConstructor() {
    Rational r;
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);
}

void TestReduceFraction() {
    {
        Rational r(4, 8);
        AssertEqual(r.Numerator(), 1);
        AssertEqual(r.Denominator(), 2);
    }
    {
        Rational r(9, 12);
        AssertEqual(r.Numerator(), 3);
        AssertEqual(r.Denominator(), 4);
    }
}

void TestNegativeFraction() {
    {
        Rational r(-5, 25);
        AssertEqual(r.Numerator(), -1);
        AssertEqual(r.Denominator(), 5);
    }
    {
        Rational r(6, -18);
        AssertEqual(r.Numerator(), -1);
        AssertEqual(r.Denominator(), 3);
    }
}

void TestPositiveFraction() {
    Rational r(-2, -3);
    AssertEqual(r.Numerator(), 2);
    AssertEqual(r.Denominator(), 3);
}

void TestZeroNumerator() {
    {
        Rational r(0, -5);
        AssertEqual(r.Numerator(), 0);
        AssertEqual(r.Denominator(), 1);
    }
    {
        Rational r(0, 5);
        AssertEqual(r.Numerator(), 0);
        AssertEqual(r.Denominator(), 1);
    }
    {
        Rational r(0, 1);
        AssertEqual(r.Numerator(), 0);
        AssertEqual(r.Denominator(), 1);
    }
}
int main() {
    TestRunner runner;
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestReduceFraction, "TestReduceFraction");
    runner.RunTest(TestNegativeFraction, "TestNegativeFraction");
    runner.RunTest(TestPositiveFraction, "TestPositiveFraction");
    runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
    return 0;
}

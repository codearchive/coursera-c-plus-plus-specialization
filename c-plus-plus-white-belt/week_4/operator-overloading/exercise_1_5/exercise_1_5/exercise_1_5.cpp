#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (this->numerator == 0)
        {
            this->denominator = 1;
        }
        if (this->denominator < 0)
        {
            this->numerator *= -1;
            this->denominator *= -1;
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
    return stream;
}


int main()
{
    {
        const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

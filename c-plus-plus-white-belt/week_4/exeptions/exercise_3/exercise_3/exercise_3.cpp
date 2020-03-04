#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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


int main()
{
    //string str[6] = { "1/2 + 1/3", "1/2+5/0", "4 /5 / 0/ 8",
    //                  "1/2 - 1/3", "1/2-5/0", "4 /5 * 0/ 8" };



    Rational r1, r2;
    char operation;
    try
    {
        string str;
        getline(cin, str);
        stringstream ss(str);
        ss >> r1 >> operation >> r2;
        switch (operation)
        {
        case '+':
            cout << r1 + r2 << endl;
            break;
        case '-':
            cout << r1 - r2 << endl;
            break;
        case '*':
            cout << r1 * r2 << endl;
            break;
        case '/':
            cout << r1 / r2 << endl;
            break;
        }

    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}

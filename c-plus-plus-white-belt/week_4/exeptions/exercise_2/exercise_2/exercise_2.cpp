#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>
#include <vector>

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
            throw invalid_argument("Invalid argument: denominator = 0");
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
        throw domain_error("Dived by 0");
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
    return stream;
}


int main()
{
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument&) {
    }

    try {
        auto r1 = Rational(1, 2);
        auto r2 = Rational(0, 1);

        auto x = r1 / r2;
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}

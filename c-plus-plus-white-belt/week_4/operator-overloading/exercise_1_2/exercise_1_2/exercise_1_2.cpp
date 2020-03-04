#include <iostream>
#include <numeric>

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

// Реализуйте для класса Rational операторы ==, + и -

bool operator==(const Rational& num1, const Rational& num2)
{
    if (num1.Numerator() == num2.Numerator() && num1.Denominator() == num2.Denominator())
    {
        return true;
    }
    return false;
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

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}

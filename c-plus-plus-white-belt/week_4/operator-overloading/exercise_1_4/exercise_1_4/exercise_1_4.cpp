#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>

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
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}

#include "phone_number.h"

#include <iostream>

using namespace std;

int main()
{
    PhoneNumber pn("+7-495-111-22-33");
    cout << pn.GetInternationalNumber() << endl;
    return 0;
}
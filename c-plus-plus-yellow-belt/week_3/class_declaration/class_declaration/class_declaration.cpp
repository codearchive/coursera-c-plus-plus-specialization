#include "rectangle.h"

#include <iostream>

using namespace std;

int main()
{
    Rectangle r(5, 2);
    cout << "Width = " << r.GetWidth() << endl;
    cout << "Height = " << r.GetHeight() << endl;
    cout << "Area = " << r.GetArea() << endl;
    cout << "Perimeter = " << r.GetPerimeter() << endl;

    return 0;
}
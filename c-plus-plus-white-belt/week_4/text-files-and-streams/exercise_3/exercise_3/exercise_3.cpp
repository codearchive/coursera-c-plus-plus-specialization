#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("input.txt");
    int a;
    int n = 0;
    int m = 0;
    input >> n >> m;
    if (n != 0 && m != 0)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                input >> a;
                cout << setw(10) << a;
                if (j != m - 1)
                {
                    input.ignore(1);
                    cout << ' ';
                }
            }
            if ( i != n - 1)
            {
                cout << endl;
            }
        }
    }
    return 0;
}
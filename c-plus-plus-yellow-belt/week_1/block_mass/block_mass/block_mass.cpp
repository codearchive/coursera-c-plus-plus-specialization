#include <iostream>

using namespace std;

int main()
{
    unsigned blocks_number;
    unsigned short density;
    cin >> blocks_number >> density;
    uint64_t sum_mass = 0;
    for (unsigned i = 0; i < blocks_number; ++i)
    {
        unsigned short width, height, depth;
        cin >> width >> height >> depth;
        sum_mass += static_cast<uint64_t>(width) * height * depth * density;
    }
    cout << sum_mass << endl;
    return 0;
}
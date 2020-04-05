#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int number;
    cin >> number;
    vector<int> temperatures(number);
    int64_t sum = 0;
    for (int& temperature : temperatures)
    {
        cin >> temperature;
        sum += temperature;
    }
    int avg_temperature = sum / number;
    unsigned number_above_average = count_if(temperatures.begin(), temperatures.end(), [&avg_temperature](int x) { return x > avg_temperature; });
    cout << number_above_average << endl;
    for (unsigned i = 0; i < static_cast<unsigned>(number); ++i)
    {
        if (temperatures[i] > avg_temperature)
        {
            cout << i << ' ';
        }
    }
}

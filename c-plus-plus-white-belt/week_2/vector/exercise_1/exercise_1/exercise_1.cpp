#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int nDays;
	cin >> nDays;
	if (nDays != 0)
	{
		vector<int> nTemperatures(nDays);
		int avr = 0;
		for (auto& temperature : nTemperatures)
		{
			cin >> temperature;
			avr += temperature;
		}
		avr /= nDays;
		int counter = 0;
		vector<int> indexes;
		for (int i = 0; i < nDays; ++i)
		{
			if (nTemperatures[i] > avr)
			{
				indexes.push_back(i);
				++counter;
			}
		}
		cout << counter << endl;
		for (auto& index : indexes)
			cout << index << ' ';
	}
	else
	{
		cout << 0 << endl << 0 << endl;
	}
	return 0;
}

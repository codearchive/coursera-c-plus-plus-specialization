#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<string> symbols;
	int number_of_symbols;
	cin >> number_of_symbols;
	for (int i = 0; i < number_of_symbols; ++i)
	{
		string symbol;
		cin >> symbol;
		symbols.push_back(symbol);
	}
	sort(symbols.begin(), symbols.end(), [](string str1, string str2)
	{
		int rep = min(str1.size(), str2.size());
		for (int j = 0; j < rep; ++j)
		{
			if (tolower(str1[j]) < tolower(str2[j]))
			{
				return true;
			}
			if (tolower(str1[j]) > tolower(str2[j]))
			{
				return false;
			}
		}
		return false;
	});

	for (const auto& sym : symbols)
	{
		cout << sym << ' ';
	}

	return 0;
}
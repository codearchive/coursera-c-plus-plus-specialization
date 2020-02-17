#include <iostream>
#include <string>
#include <map>

using namespace std;

bool BuildCharCounters(const string& str1, const string& str2)
{
	map<char, int> map_of_str1;
	map<char, int> map_of_str2;
	
	for (const auto& letter : str1)
	{
		map_of_str1[letter]++;
	}

	for (const auto& letter : str2)
	{
		map_of_str2[letter]++;
	}

	return map_of_str1 == map_of_str2;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string s1, s2;
		cin >> s1 >> s2;
		if (BuildCharCounters(s1, s2))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}
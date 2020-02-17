#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void add_new_line(map<int, vector<string>>& bus_lines, int& line_number, vector<string>& bus_stops)
{
	for (const auto& line : bus_lines)
	{
		if(line.second == bus_stops)
		{
			cout << "Already exists for " << line.first << endl;
			return;
		}
	}
	cout << "New bus " << line_number << endl;
	bus_lines[line_number] = bus_stops;
	++line_number;
}

int main()
{
	map<int, vector<string>> m;
	int n;
	cin >> n;
	int bus_number = 1;
	for (int i = 0; i < n; ++i)
	{
		int stop_number;
		cin >> stop_number;
		vector<string> temp_vec;
		for (int j = 0; j < stop_number; ++j)
		{
			string stop;
			cin >> stop;
			temp_vec.push_back(stop);
		}
		add_new_line(m, bus_number, temp_vec);
	}

	return 0;
}

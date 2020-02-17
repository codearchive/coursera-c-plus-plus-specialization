#include <iostream>
#include <set>
#include <string>
#include <map>

using namespace std;

void add_bus(map<int, set<string>>& buses, int& bus_number, set<string>& new_stops)
{
	buses[bus_number] = new_stops;
	++bus_number;
}

void check_stop(map<int, set<string>>& buses, int& bus_number, set<string>& new_stops)
{
	for (const auto& line_and_stops : buses)
	{
		if (line_and_stops.second == new_stops)
		{
			cout << "Already exists for " << line_and_stops.first << endl;
			return;
		}
	}
	cout << "New bus " << bus_number << endl;
	add_bus(buses, bus_number, new_stops);
}

int main()
{
	map<int, set<string>> buses;
	int bus_number = 1;
	int number_of_operations = 0;
	cin >> number_of_operations;
	for (int i = 0; i < number_of_operations; ++i)
	{
		int stops_number;
		cin >> stops_number;
		set<string> stops;
		for (int j = 0; j < stops_number; ++j)
		{
			string stop;
			cin >> stop;
			stops.insert(stop);
		}
		check_stop(buses, bus_number, stops);
	}
	return 0;
}

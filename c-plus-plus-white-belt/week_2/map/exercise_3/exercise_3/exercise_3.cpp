#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void new_bus(vector<map<string, vector<string>>>& all_buses, string& bus, vector<string>& stops)
{
	map<string, vector<string>> temp_new_bus = { {bus, stops} };
	all_buses.push_back(temp_new_bus);
}

vector<string> buses_for_stop(const vector<map<string, vector<string>>>& all_buses, const string& stop)
{
	vector<string> result;
	for (const auto& map_for_bus : all_buses)
	{
		for (const auto& bus : map_for_bus)
		{
			for (const auto& stop_in_line : bus.second)
			{
				if (stop_in_line == stop)
				{
					result.push_back(bus.first);
				}
			}
		}
	}
	return result;
}

void print_result(vector<string>& res, string curr_bus = "non")
{
	if (curr_bus == "non")
	{
		for (const auto& r : res)
		{
			cout << r << ' ';
		}
	}
	else
	{
		for (const auto& r : res)
		{
			if (r != curr_bus)
			{
				cout << r << ' ';
			}
		}
	}
	cout << endl;
}

bool stops_for_bus(const vector<map<string, vector<string>>>& all_buses, string& bus_number)
{
	vector<string> result;
	bool exist = false;
	for (const auto& map_for_bus : all_buses)
	{
		for (const auto& bus : map_for_bus)
		{
			if (bus.first == bus_number)
			{
				exist = true;
				for (const auto& stop_in_line : bus.second)
				{
					result = buses_for_stop(all_buses, stop_in_line);
					if (result.empty() || result.size() == 1)
					{
						cout << "Stop " << stop_in_line << ": no interchange" << endl;
					}
					else
					{
						cout << "Stop " << stop_in_line << ": ";
						print_result(result, bus_number);
					}
				}

			}
		}
	}
	return exist;
}

void all_buses(const vector<map<string, vector<string>>>& all_buses)
{
	map<string, vector<string>> temp_bus;
	if (!all_buses.empty())
	{
		for (const auto& map_for_bus : all_buses)
		{
			for (const auto& bus : map_for_bus)
			{
				temp_bus[bus.first] = bus.second;
			}
		}

		for (const auto& bus : temp_bus)
		{
			cout << "Bus " << bus.first << ": ";
			for (const auto& stop_in_line : bus.second)
			{
				cout << stop_in_line << ' ';
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No buses" << endl;
	}
}

int main()
{
	vector<map<string, vector<string>>> buses;
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string cmd;
		cin >> cmd;
		if (cmd == "NEW_BUS")
		{

			string new_bus_line;
			int number_of_stops;
			cin >> new_bus_line >> number_of_stops;
			vector<string> stops;
			while (number_of_stops > 0)
			{
				string stop;
				cin >> stop;
				stops.push_back(stop);
				--number_of_stops;
			}
			new_bus(buses, new_bus_line, stops);
		}
		if (cmd == "BUSES_FOR_STOP")
		{
			vector<string> res;
			string stop;
			cin >> stop;
			res = buses_for_stop(buses, stop);
			if (res.empty())
			{
				cout << "No stop" << endl;
			}
			else
			{
				print_result(res);
			}

		}
		if (cmd == "STOPS_FOR_BUS")
		{
			string bus;
			cin >> bus;
			bool isExist;
			isExist = stops_for_bus(buses, bus);
			if (!isExist)
			{
				cout << "No bus" << endl;
			}
		}
		if (cmd == "ALL_BUSES")
		{
			all_buses(buses);
		}
	}



	return 0;
}
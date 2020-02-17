#include <iostream>
#include <string>
#include <map>

using namespace std;

void change_capital(map<string, string>& countries, string& country, string& new_capital)
{
	if (countries.count(country) && countries[country] == new_capital)
	{
		cout << "Country " << country << " hasn't changed its capital" << endl;
		return;
	}
	if (countries.count(country) && countries[country] != new_capital)
	{
		cout << "Country " << country << " has changed its capital from " << countries[country] << " to " << new_capital << endl;
	}
	if (!countries.count(country))
	{
		cout << "Introduce new country " << country << " with capital " << new_capital << endl;
	}
	countries[country] = new_capital;
}

void rename(map<string, string>& countries, string& old_country_name, string& new_country_name)
{
	if (!countries.count(old_country_name) || countries.count(new_country_name) || countries.count(old_country_name) && old_country_name == new_country_name)
	{
		cout << "Incorrect rename, skip" << endl;
		return;
	}
	string capital = countries[old_country_name];
	cout << "Country " << old_country_name << " with capital " << capital << " has been renamed to " << new_country_name << endl;
	countries.erase(old_country_name);
	countries[new_country_name] = capital;
}

void about(map<string, string>& countries, string& country)
{
	if (!countries.count(country))
	{
		cout << "Country " << country << " doesn't exist" << endl;
		return;
	}
	cout << "Country " << country << " has capital " << countries[country] << endl;
}

void dump(map<string, string>& countries)
{
	if (countries.empty())
	{
		cout << "There are no countries in the world" << endl;
		return;
	}
	for (const auto& country : countries)
	{
		cout << country.first << '/' << country.second << ' ';
	}
	cout << endl;
}

int main()
{
	map<string, string> countries;
	int n = 0;
	cin >> n;
	for (int i  = 0; i < n; ++i)
	{
		string cmd;
		cin >> cmd;
		if (cmd == "CHANGE_CAPITAL")
		{
			string country, new_capital;
			cin >> country >> new_capital;
			change_capital(countries, country, new_capital);
		}
		else if (cmd == "RENAME")
		{
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;
			rename(countries, old_country_name, new_country_name);
		}
		else if (cmd == "ABOUT")
		{
			string country;
			cin >> country;
			about(countries, country);
		}
		else if (cmd == "DUMP")
		{
			dump(countries);
		}
	}
	return 0;
}
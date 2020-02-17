#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void add(vector<vector<string>>& month, int day_index, string task)
{
	month[day_index - 1].push_back(task);
}

void dump(vector<vector<string>>& month, int day_index)
{
	cout << month[day_index - 1].size() << ' ';
	for (const auto& task : month[day_index - 1])
	{
		cout << task << ' ';
	}
	cout << endl;
}

void next(vector<vector<string>>& month, vector<int>& days_in_month, int& month_index, vector <vector<string>>& next_month)
{
	if (days_in_month[month_index] <= days_in_month[(month_index + 1) % 12])
	{
		for (int i = 0; i < month.size(); ++i)
		{
			next_month[i] = month[i];
		}
	}
	else
	{
		for (int i = 0; i < next_month.size(); ++i)
		{
			next_month[i] = month[i];
			if (i + 1 == next_month.size())
			{
				for (int j = i + 1; j < month.size(); ++j)
				{
					next_month[i].insert(end(next_month[i]), begin(month[j]), end(month[j]));
				}
			}
		}
	}
	month.clear();
	month.resize(days_in_month[(month_index + 1) % 12]);
	month = next_month;
	++month_index %= 12;
}


int main()
{
	vector<int> days_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int current_month_index = 0;
	vector<vector<string>> current_month(days_in_month[current_month_index]);

	int n = 0;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		string func;
		cin >> func;
		if (func == "ADD")
		{
			int day = 0;
			string task;
			cin >> day >> task;
			add(current_month, day, task);
		}
		else if (func == "DUMP")
		{
			int day = 0;
			cin >> day;
			dump(current_month, day);
		}
		else if (func == "NEXT")
		{
			vector<vector<string>> next_month(days_in_month[(current_month_index + 1) % 12]);
			next(current_month, days_in_month, current_month_index, next_month);
		}
	}
	return 0;
}
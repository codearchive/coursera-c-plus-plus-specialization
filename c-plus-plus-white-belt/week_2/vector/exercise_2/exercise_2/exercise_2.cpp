#include <iostream>
#include <vector>
#include <string>

using namespace std;

void come(vector<bool>& queue, int number)
{
	if (number > 0 )
	{
		queue.resize(queue.size() + number, false);
	}
	else
	{
		queue.resize(queue.size() + number);
	}
}

void worry(vector<bool>& queue, int index)
{
	queue[index] = true;
}

void quiet(vector<bool>& queue, int index)
{
	queue[index] = false;
}

void worry_count(vector<bool>& queue)
{
	int counter = 0;
	for (auto person : queue)
	{
		if (person)
		{
			++counter;
		}
	}
	cout << counter << endl;
}

int main()
{
	vector<bool> queueWorry;
	int q = 0;
	cin >> q;
	string cmd;
	int cmd_index;
	for (int i = 0; i < q; ++i)
	{
		cin >> cmd;
		if (cmd == "WORRY")
		{
			cin >> cmd_index;
			worry(queueWorry, cmd_index);
		}
		else if (cmd == "QUIET")
		{
			cin >> cmd_index;
			quiet(queueWorry, cmd_index);
		}
		else if (cmd == "COME")
		{
			cin >> cmd_index;
			come(queueWorry, cmd_index);
		}
		else if (cmd == "WORRY_COUNT")
		{
			worry_count(queueWorry);
		}
	}
	return 0;
}

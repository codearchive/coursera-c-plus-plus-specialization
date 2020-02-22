#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
bool get_module(int x, int y)
{
	if (x < 0)
	{
		x *= -1;
	}
	if (y < 0)
	{
		y *= -1;
	}
	return (x < y);
}
*/

int main()
{
	int n;
	cin >> n;
	vector<int> numbers;
	for (int i = 0; i < n; ++i)
	{
		int number;
		cin >> number;
		numbers.push_back(number);
	}
	
	//sort(begin(numbers), end(numbers), get_module); //Using comparison function.
	sort(begin(numbers), end(numbers), [](int x, int y) // Using lambda-function.
	{
		if (x < 0)
		{
			x *= -1;
		}
		if (y < 0)
		{
			y *= -1;
		}
		return (x < y);
	});

	for (const auto& num : numbers)
	{
		cout << num << ' ';
	}

}
#include <iostream>
#include <string>
#include <set>
#include <map>
#include "BuildMapValuesSet.h"

using namespace std;

int main()
{
	set<string> values = BuildMapValuesSet({
	{1, "odd"},
	{2, "even"},
	{3, "odd"},
	{4, "even"},
	{5, "odd"}
		});

	for (const string& value : values) {
		cout << value << endl;
	}

	return 0;
}

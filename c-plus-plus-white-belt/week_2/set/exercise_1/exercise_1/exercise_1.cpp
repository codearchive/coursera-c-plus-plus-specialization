#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
	set<string> words;
	int number_words = 0;
	cin >> number_words;
	for (int i = 0; i < number_words; ++i)
	{
		string word;
		cin >> word;
		words.insert(word);
	}
	cout << words.size();
}
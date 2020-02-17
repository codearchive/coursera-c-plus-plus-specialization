#include <iostream>
#include <set>
#include <string>
#include <map>

using namespace std;

void add(map<string, set<string>>& words, string& word1, string& word2)
{
	words[word1].insert(word2);
	words[word2].insert(word1);
}

void count(map<string, set<string>>& words, const string& word)
{
	cout << words[word].size() << endl;
}

void check( map<string, set<string>>& words, const string& word1, const string& word2)
{
	if (words.count(word1) && words[word1].count(word2))
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}

int main()
{
	map<string, set<string>> words;
	int number_of_operations = 0;
	cin >> number_of_operations;
	for (int i = 0; i < number_of_operations; ++i)
	{
		string command;
		cin >> command;
		if (command == "ADD")
		{
			string word1, word2;
			cin >> word1 >> word2;
			add(words, word1, word2);
		}
		else if (command == "COUNT")
		{
			string word;
			cin >> word;
			count(words, word);
		}
		else if (command == "CHECK")
		{
			string word1, word2;
			cin >> word1 >> word2;
			check(words, word1, word2);
		}
	}
	return 0;
}
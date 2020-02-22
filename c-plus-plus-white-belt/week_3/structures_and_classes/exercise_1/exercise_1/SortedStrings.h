#pragma once
#include <string>
#include <vector>
#include <algorithm>

class SortedStrings {
public:
	void AddString(const std::string& s) {
		sortedVector.push_back(s);
	}

	std::vector<std::string> GetSortedStrings() {
		sort(begin(sortedVector), end(sortedVector), [](const std::string& l, const std::string& r) {
			return std::lexicographical_compare(
				std::begin(l), std::end(l),
				std::begin(r), std::end(r)
			);
		});

		return sortedVector;
	}
private:
	std::vector<std::string> sortedVector;
};

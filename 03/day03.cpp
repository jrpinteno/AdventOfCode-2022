#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <numeric>

std::vector<std::string> parseInput(const std::filesystem::path& filePath) {
	std::string currentLine;
	std::ifstream fileStream{filePath};
	std::vector<std::string> inputLines;

	while (std::getline(fileStream, currentLine)) {
		inputLines.push_back(currentLine);
	}

	return inputLines;
}

std::unordered_map<char, int> priorities;

void assignPriorities() {
	int priority = 1;

	for (char character = 'a'; character <= 'z'; character++) {
		priorities.insert({character, priority});
		priorities.insert({std::toupper(character), priority + 26});
		priority += 1;
	}
}

int part1(const std::vector<std::string>& rucksacks) {
	std::vector<char> common;

	for (std::string_view rucksack : rucksacks) {
		std::set<char> compartment1;
		std::set<char> compartment2;
		auto rucksackLength = rucksack.size() / 2;

		for (int i = 0; i < rucksackLength; i++) {
			compartment1.insert(rucksack[i]);
			compartment2.insert(rucksack[i + rucksackLength]);
		}

		std::set_intersection(compartment1.begin(), compartment1.end(), compartment2.begin(), compartment2.end(), std::back_inserter(common));
	}

	return std::accumulate(common.begin(), common.end(), 0, [](int sum, const char& s) {
		return sum + priorities[s];
	});
}

int part2(const std::vector<std::string>& rucksacks) {
	std::vector<char> common;
	std::unordered_map<char, int> occurrences;

	int i = 0;
	for (std::string_view rucksack: rucksacks) {
		i += 1;
		std::set<char> unique { rucksack.begin(), rucksack.end() };

		for (auto const item : unique) {
			if (occurrences.find(item) == occurrences.end()) {
				occurrences.insert({item, 1});
			} else {
				occurrences[item]++;
			}
		}

		if (i % 3 == 0) {
			auto max = std::max_element(occurrences.begin(), occurrences.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
				return a.second < b.second;
			});
			common.push_back(max->first);

			occurrences.erase(occurrences.begin(), occurrences.end());
			i = 0;
		}
	}

	return std::accumulate(common.begin(), common.end(), 0, [](int sum, const char& s) {
		return sum + priorities[s];
	});
}

int main() {
	assignPriorities();

	auto rucksacks = parseInput("input03.txt");

	std::cout << part1(rucksacks) << std::endl;
	std::cout << part2(rucksacks) << std::endl;
}


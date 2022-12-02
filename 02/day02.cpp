#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> parseInput(const std::filesystem::path& filePath) {
	std::string currentLine;
	std::ifstream fileStream{filePath};
	std::vector<std::string> inputLines;

	while (std::getline(fileStream, currentLine)) {
		inputLines.push_back(currentLine);
	}

	return inputLines;
}

std::unordered_map<std::string, int> outcomes1 = {
		{"A X", 1+3},
		{"A Y", 2+6},
		{"A Z", 3+0},
		{"B X", 1+0},
		{"B Y", 2+3},
		{"B Z", 3+6},
		{"C X", 1+6},
		{"C Y", 2+0},
		{"C Z", 3+3},
};

std::unordered_map<std::string, int> outcomes2 = {
		{"A X", 0+3},
		{"A Y", 3+1},
		{"A Z", 6+2},
		{"B X", 0+1},
		{"B Y", 3+2},
		{"B Z", 6+3},
		{"C X", 0+2},
		{"C Y", 3+3},
		{"C Z", 6+1},
};

int main() {
	int result1 = 0;
	int result2 = 0;
	auto combats = parseInput("input02.txt");

	for (const auto& combat : combats) {
		auto outcome1 = outcomes1[combat];
		result1 += outcome1;

		auto outcome2 = outcomes2[combat];
		result2 += outcome2;
	}

	std::cout << result1 << std::endl;
	std::cout << result2 << std::endl;
}
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <numeric>

std::vector<int> parseInput(const std::filesystem::path& filePath) {
	std::string currentLine;
	std::ifstream fileStream{filePath};
	std::vector<int> inputLines;

	while (std::getline(fileStream, currentLine)) {
		inputLines.push_back(currentLine.empty() ? 0 : std::stoi(currentLine));
	}

	return inputLines;
}

std::vector<int> sumCalories(std::vector<int>& snacks) {
	int elfCalories = 0;
	std::vector<int> elvesCalories;

	for (auto snack : snacks) {
		if (snack != 0) {
			elfCalories += snack;
			continue;
		}

		elvesCalories.push_back(elfCalories);
		elfCalories = 0;
	}

	return elvesCalories;
}

void partOne(std::vector<int>& snacks) {
	std::cout << snacks.front() << std::endl;
}

void partTwo(std::vector<int>& snacks) {
	std::cout << snacks[0] + snacks[1] + snacks[2] << std::endl;
}

int main () {
	auto snacks = parseInput("input.txt");
	auto elvesSnacks = sumCalories(snacks);
	std::sort(elvesSnacks.begin(), elvesSnacks.end(), std::greater<>());

	partOne(elvesSnacks);
	partTwo(elvesSnacks);
}

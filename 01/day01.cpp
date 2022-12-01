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

void partOne(std::vector<int>& snacks) {
	int maxCalories = 0;
	int elfCalories = 0;

	for (auto calories : snacks) {
		if (calories != 0) {
			elfCalories += calories;
			continue;
		}

		maxCalories = std::max(maxCalories, elfCalories);
		elfCalories = 0;
	}

	std::cout << maxCalories << std::endl;
}

void partTwo(std::vector<int>& snacks) {
	int elfCalories = 0;
	std::vector<int> elves;

	for (auto snack : snacks) {
		if (snack != 0) {
			elfCalories += snack;
			continue;
		}

		elves.push_back(elfCalories);
		elfCalories = 0;
	}

	std::sort(elves.begin(), elves.end(), std::greater<>());

	std::cout << elves[0] + elves[1] + elves[2] << std::endl;
}

int main () {
	auto snacks = parseInput("input.txt");

	partOne(snacks);
	partTwo(snacks);
}

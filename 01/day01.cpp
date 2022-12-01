#include <iostream>
#include <filesystem>
#include <fstream>

int main () {
	int maxCalories = 0;
	int elfCalories = 0;

	std::filesystem::path filePath = "input.txt";

	std::ifstream fileStream{filePath};
	std::string currentLine;

	while (std::getline(fileStream, currentLine)) {
		if (!currentLine.empty()) {
			elfCalories += std::stoi(currentLine);
			continue;
		}

		maxCalories = std::max(maxCalories, elfCalories);
		elfCalories = 0;
	}

	std::cout << maxCalories << std::endl;
}

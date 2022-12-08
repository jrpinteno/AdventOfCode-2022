#include "Utils.h"

#include <fstream>
#include <iostream>
namespace Utils {
	std::vector<std::string> readLines(const std::filesystem::path &filePath) {
		std::string currentLine;
		std::ifstream fileStream{filePath};
		std::vector<std::string> inputLines;

		while (std::getline(fileStream, currentLine)) {
			inputLines.push_back(currentLine);
		}

		return inputLines;
	}

	std::string readString(const std::filesystem::path &filePath) {
		std::string line;
		std::ifstream fileStream{filePath};
		std::getline(fileStream, line);

		return line;
	}

	std::vector<int> readIntLines(const std::filesystem::path& filePath) {
		std::string currentLine;
		std::ifstream fileStream{filePath};
		std::vector<int> inputLines;

		while (std::getline(fileStream, currentLine)) {
			inputLines.push_back(std::stoi(currentLine));
		}

		return inputLines;
	}

	std::vector<std::string> split(std::string_view line, char delimiter) {
		std::vector<std::string> parts;
		size_t index = 0;

		while ((index = line.find(delimiter)) != std::string::npos) {
			const auto part = line.substr(0, index);
			parts.emplace_back(part);
			line.remove_prefix(index + 1);
		}

		parts.emplace_back(line);

		return parts;
	}

	std::vector<std::string> split(const std::string& line, char delimiter) {
		return split(std::string_view(line), delimiter);
	}

	std::vector<std::vector<int>> readIntGrid(const std::filesystem::path& filePath) {
		std::ifstream fileStream{filePath};
		std::vector<std::vector<int>> grid;

		std::string row;

		while(std::getline(fileStream, row)) {
			std::vector<int> rowVector;

			for (char c : row) {
				rowVector.push_back(c - '0');
			}

			grid.push_back(rowVector);
		}

		return grid;
	}
}


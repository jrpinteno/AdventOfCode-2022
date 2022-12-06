#include "Utils.h"

#include <fstream>

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
}


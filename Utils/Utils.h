//
// Created by Xavi R. Pinteño on 6.12.2022.
//

#ifndef ADVENTOFCODE2022_UTILS_H
#define ADVENTOFCODE2022_UTILS_H

#include <vector>
#include <filesystem>
#include <array>
#include <iostream>
#include <utility>

namespace Utils {
	std::vector<std::string> readLines(const std::filesystem::path& filePath);
	std::vector<std::vector<std::string>> readBlocks(const std::filesystem::path &filePath);
		std::string readString(const std::filesystem::path &filePath);
	std::vector<std::vector<int>> readIntGrid(const std::filesystem::path& filePath);

	std::vector<std::string> split(const std::string& line, char delimiter = ' ');
	std::vector<std::string> split(std::string_view line, char delimiter = ' ');
};

#endif //ADVENTOFCODE2022_UTILS_H

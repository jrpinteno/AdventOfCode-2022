//
// Created by Xavi R. Pinteño on 6.12.2022.
//

#ifndef ADVENTOFCODE2022_UTILS_H
#define ADVENTOFCODE2022_UTILS_H

#include <vector>
#include <filesystem>

namespace Utils {
	std::vector<std::string> readLines(const std::filesystem::path& filePath);
	std::string readString(const std::filesystem::path &filePath);
};


#endif //ADVENTOFCODE2022_UTILS_H

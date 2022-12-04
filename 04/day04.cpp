#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <regex>

std::vector<std::string> parseInput(const std::filesystem::path& filePath) {
	std::string currentLine;
	std::ifstream fileStream{filePath};
	std::vector<std::string> inputLines;

	while (std::getline(fileStream, currentLine)) {
		inputLines.push_back(currentLine);
	}

	return inputLines;
}

int fullOverlap(const std::pair<int, int> firstElf, const std::pair<int, int> secondElf) {
	if (firstElf.first <= secondElf.first && firstElf.second >= secondElf.second) {
		return 1;
	} else if (firstElf.first >= secondElf.first && firstElf.second <= secondElf.second) {
		return 1;
	} else {
		return 0;
	}
}

int sectionOverlap(const std::pair<int, int> firstElf, const std::pair<int, int> secondElf) {
	if (firstElf.first <= secondElf.first && firstElf.second >= secondElf.first) {
		return 1;
	} else if (firstElf.first <= secondElf.second && firstElf.second >= secondElf.second) {
		return 1;
	} else if (secondElf.first <= firstElf.first && secondElf.second >= firstElf.first) {
		return 1;
	} else if (secondElf.first <= firstElf.second && secondElf.second >= firstElf.second) {
		return 1;
	}

	return 0;
}

int main() {
	auto elves = parseInput("input04.txt");

	const std::regex ranges(R"((\d+)-(\d+),(\d+)-(\d+))");
	std::smatch match;
	int overlap = 0;
	int overlapSomehow = 0;

	for (const auto& line : elves) {
		std::regex_match(line, match, ranges);
		std::pair<int, int> firstElf = {std::stoi(match[1].str()), std::stoi(match[2].str()) };
		std::pair<int, int> secondElf = {std::stoi(match[3].str()), std::stoi(match[4].str()) };

		overlap += fullOverlap(firstElf, secondElf);
		overlapSomehow += sectionOverlap(firstElf, secondElf);
	}

	std::cout << overlap << std::endl;
	std::cout << overlapSomehow << std::endl;
}
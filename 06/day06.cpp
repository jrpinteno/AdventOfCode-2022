#include "../Utils/Utils.h"

#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <array>

std::string generateRegex(int window) {
	std::string regex = "(.)";

	for (int i = 1; i < window; i++) {
		for (int j = 1; j <= i; j++) {
			regex.append("(?!");
			regex.append("\\");
			regex.append(std::to_string(j));
			regex.append(")");
		}

		regex.append("(.)");
	}

	return regex;
}

void solveWithRegex(const std::string& text, const int window) {
	std::regex pattern(generateRegex(window));
	std::smatch match;
	std::regex_search(text, match, pattern);

	std::cout << match.position() + match.length() << std::endl;
}

void solveWithSet(const std::string& text, const int window) {
	for (auto it = text.begin(); it != text.end(); it++) {
		auto windowChars = std::set(it, it + window);

		if (windowChars.size() == window) {
			std::cout << std::distance(text.begin(), it) + window << std::endl;
			break;
		}
	}
}

bool hasRepeatedChars(const std::array<int, 26>& histogram) {
	return std::any_of(histogram.begin(), histogram.end(), [](const int value) {
		return value > 1;
	});
}

void solveWithHistogram(const std::string& text, const int window) {
	std::array<int, 26> histogram = { 0 };

	for (int i = 0; i < window; i++) {
		histogram[text[i] - 'a']++;
	}

	if (!hasRepeatedChars(histogram)) {
		std::cout << window + 1 << std::endl;
		return;
	}

	for (int i = window; i < text.length(); i++) {
		histogram[text[i - window] - 'a']--;
		histogram[text[i] - 'a']++;

		if (!hasRepeatedChars(histogram)) {
			std::cout << i + 1 << std::endl;
			return;
		}
	}
}

int main() {
	auto line = Utils::readString("input06.txt");

	solveWithRegex(line, 4);
	solveWithSet(line, 4);
	solveWithHistogram(line, 4);
	solveWithRegex(line, 14);
	solveWithSet(line, 14);
	solveWithHistogram(line, 14);
}



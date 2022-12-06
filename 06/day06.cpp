#include "../Utils/Utils.h"

#include <iostream>
#include <string>
#include <regex>
#include <set>

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

int main() {
	auto line = Utils::readString("input06.txt");

	solveWithRegex(line, 4);
	solveWithSet(line, 4);
	solveWithRegex(line, 14);
	solveWithSet(line, 14);
}



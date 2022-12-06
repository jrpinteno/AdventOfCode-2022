#include "../Utils/Utils.h"

#include <iostream>
#include <string>
#include <regex>

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

void solve(const std::string& text, const int window) {
	std::regex pattern(generateRegex(window));
	std::smatch match;
	std::regex_search(text, match, pattern);

	std::cout << match.position() + match.length() << std::endl;
}

int main() {
	auto line = Utils::readString("input06.txt");

	solve(line, 4);
	solve(line, 14);
}

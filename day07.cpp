#include "../Utils/Utils.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <stack>
#include <string>
#include <numeric>
#include <utility>

std::vector<std::string> split(std::string_view line, char delimiter = ' ') {
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

void processCommand(std::string_view line, std::stack<std::string>& stack, std::unordered_map<std::string, size_t>& sizes) {
	const auto commandParts = split(line);

	if (commandParts[1] == "cd") {
		if (commandParts[2] == "..") {
			stack.pop();
		} else if (commandParts[2][0] != '/') {
			auto path = stack.top() + commandParts[2] + "/";
			stack.push(path);
			sizes[path] = 0;
		} else {
			while (!stack.empty()) {
				stack.pop();
			}

			stack.push(commandParts[2]);
			sizes["/"] = 0;
		}
	}
}

void processContent(std::string_view line, std::stack<std::string>& stack, std::unordered_map<std::string, size_t>& sizes) {
	const auto contentParts = split(line);
	const auto size = std::stoi(std::string(contentParts[0]));

	auto copyStack(stack);

	while (!copyStack.empty()) {
		sizes[copyStack.top()] += size;
		copyStack.pop();
	}
}

int main() {
	std::unordered_map<std::string, size_t> sizes;
	std::stack<std::string> dirStack;

	auto lines = Utils::readLines("input07.txt");

	for (std::string_view line : lines) {
		switch (line[0]) {
			case '$':
				processCommand(line, dirStack, sizes);
				break;

			case 'd':
				break;

			default:
				processContent(line, dirStack, sizes);
				break;
		}
	}

	const auto sumSizes = std::accumulate(sizes.begin(), sizes.end(), 0, [](size_t sum, const std::pair<std::string_view, size_t>& pair) {
		if (pair.second < 100000) {
			sum += pair.second;
		}

		return sum;
	});

	std::cout << "Part 1: " << sumSizes << std::endl;

	std::set<size_t> orderedSizes;

	for (const auto& pair : sizes) {
		orderedSizes.insert(pair.second);
	}

	size_t free = 70000000 - sizes["/"];
	size_t missing = 30000000 - free;

	auto it = orderedSizes.upper_bound(missing);
	std::cout << "Part 2 : " << *it << std::endl;
}
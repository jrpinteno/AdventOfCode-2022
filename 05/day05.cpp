#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <stack>
#include <array>

struct Move {
	int amount;
	int fromStack;
	int toStack;
};

std::vector<std::string> parseInput(const std::filesystem::path& filePath) {
	std::string currentLine;
	std::ifstream fileStream{filePath};
	std::vector<std::string> inputLines;

	while (std::getline(fileStream, currentLine)) {
		inputLines.push_back(currentLine);
	}

	return inputLines;
}

Move parseMove(const std::string& line) {
	const std::regex movement(R"(move (\d+) from (\d+) to (\d+))");
	std::smatch match;
	std::regex_match(line, match, movement);

	return Move{
		.amount = std::stoi(match[1].str()), .fromStack = std::stoi(match[2].str()), .toStack = std::stoi(match[3].str())
	};
}

std::vector<Move> parseMoves(const std::vector<std::string>& moveLines) {
	std::vector<Move> parsedMove {};

	for (const auto& line : moveLines) {
		parsedMove.push_back(parseMove(line));
	}

	return parsedMove;
}

std::pair<std::vector<std::string>, std::vector<std::string>> parseMovesAndCrates(const std::vector<std::string>& input) {
	std::vector<std::string> stacksInput;
	std::vector<std::string> movesInput;

	const auto empty = std::find(input.begin(), input.end(), "");

	std::copy(input.begin(), empty, std::back_inserter(stacksInput));
	std::copy(std::next(empty), input.end(), std::back_inserter(movesInput));

	return {stacksInput, movesInput};
}

int findNumberStacks(const std::string& line) {
	std::regex stacksNumber(R"(.*(?:\D|^)(\d+))");
	std::smatch match;
	std::regex_match(line, match, stacksNumber);

	return std::stoi(match[1].str());
}

using CrateStack = std::stack<char>;

CrateStack parseSingleStack(size_t stackIndex, const std::vector<std::string>& crateLines, const char delimiter = ' ') {
	CrateStack stack;

	for (int index = crateLines.size() - 2; index >= 0; index--) {
		const auto& level = crateLines[index];
		const auto& crate = level[stackIndex];

		if (crate == delimiter) {
			break;
		}

		stack.push(crate);
	}

	return stack;
}

std::vector<CrateStack> createStacks(const std::vector<std::string>& crateLines) {
	auto stacks = std::vector<std::stack<char>>{};

	for (int stackIndex = 0; stackIndex < crateLines[crateLines.size() - 1].size(); stackIndex++) {
		if (crateLines[crateLines.size() - 1][stackIndex] == ' ') {
			continue;
		}

		auto stack = parseSingleStack(stackIndex, crateLines);

		stacks.emplace_back(stack);
	}

	return stacks;
};

void performCrateMover9000(const Move& move, CrateStack& fromStack, CrateStack& toStack) {
	for (int i = 0; i < move.amount; i++) {
		toStack.push(fromStack.top());
		fromStack.pop();
	}
}

void performCrateMover9001(const Move& move, CrateStack& fromStack, CrateStack& toStack) {
	CrateStack temp;
	for (int i = 0; i < move.amount; i++) {
		temp.push(fromStack.top());
		fromStack.pop();
	}

	for (int i = 0; i < move.amount; i++) {
		toStack.push(temp.top());
		temp.pop();
	}
}

std::string obtainTop(const std::vector<CrateStack>& stacks) {
	std::string top;

	for (auto & stack : stacks) {
		top.push_back(stack.top());
	}

	return top;
}

int main() {
	auto everything = parseInput("input05.txt");

	const auto [stackLines, moveLines] = parseMovesAndCrates(everything);
	const auto moves = parseMoves(moveLines);
	auto stacks9000 = createStacks(stackLines);
	auto stacks9001 = createStacks(stackLines);

	for (const auto& move : moves) {
		performCrateMover9000(move, stacks9000[move.fromStack - 1], stacks9000[move.toStack - 1]);
		performCrateMover9001(move, stacks9001[move.fromStack - 1], stacks9001[move.toStack - 1]);
	}

	std::cout << obtainTop(stacks9000) <<  std::endl;
	std::cout << obtainTop(stacks9001) <<  std::endl;
}
#include "../Utils/Utils.h"

#include <map>
#include <queue>
#include <regex>
#include <cmath>

void parseMonkey(const std::vector<std::string>& monkey, std::map<int, std::queue<int>>& monkeyItems, std::map<int, std::vector<std::string>>& monkeyOperations, std::map<int, std::array<int, 3>>& monkeyTests) {
	const std::regex monkeyPattern(R"(Monkey (\d+):)");
	std::smatch matchMonkey;
	std::regex_match(monkey[0], matchMonkey, monkeyPattern);
	auto monkeyId = std::stoi(matchMonkey[1].str());


	// ITEMS
	const std::regex itemsPattern(R"(\s+Starting items: (\d+(?:,\s*\d+)*))");
	std::smatch matchItems;
	std::regex_match(monkey[1], matchItems, itemsPattern);
	auto items1 = matchItems[1].str();
	std::queue<int> items;

	std::smatch match;
	std::regex regex(R"(\d+)");

	for (std::sregex_iterator it(items1.begin(), items1.end(), regex), end; it != end; it++) {
		const std::smatch& matchItem = *it;
		items.push(std::stoi(matchItem.str()));
	}

	monkeyItems[monkeyId] = items;

	// OPERATION
	const std::regex operationPattern(R"(\s+Operation: new = (.*))");
	std::smatch matchOperation;
	std::regex_match(monkey[2], matchOperation, operationPattern);
	auto operation = Utils::split(matchOperation[1].str());
	monkeyOperations[monkeyId] = operation;


	// TEST
	const std::regex testPattern(R"(\s+Test: divisible by (\d+))");
	std::smatch matchTest;
	std::regex_match(monkey[3], matchTest, testPattern);


	// TRUE CASE
	const std::regex truePattern(R"(\s+If true: throw to monkey (\d+))");
	std::smatch matchTrue;
	std::regex_match(monkey[4], matchTrue, truePattern);

	// FALSE CASE
	const std::regex falsePattern(R"(\s+If false: throw to monkey (\d+))");
	std::smatch matchFalse;
	std::regex_match(monkey[5], matchFalse, falsePattern);

	std::array<int, 3> testOp({std::stoi(matchTest[1].str()), std::stoi(matchTrue[1].str()), std::stoi(matchFalse[1].str())});
	monkeyTests[monkeyId] = testOp;
}

void processMonkey(int monkeyId, std::map<int, int>& monkeyInspections, std::map<int, std::queue<int>>& monkeyItems, const std::vector<std::string>& operation, const std::array<int, 3>& test) {
	auto items = monkeyItems[monkeyId];
std::cout << "Monkey " << monkeyId << ":" << std::endl;
	while(!items.empty()) {
		monkeyInspections[monkeyId] += 1;

		auto item = items.front();
		items.pop();

		std::cout << "  Monkey inspects an item with a worry level of "<< item << std::endl;

		int newWorryLevel;
		int op2;

		if (operation[0][0] == 'o') {
			newWorryLevel = item;
		} else {
			newWorryLevel = std::stoi(operation[0]);
		}

		if (operation[2][0] == 'o') {
			op2 = item;
		} else {
			op2 = std::stoi(operation[2]);
		}

		std::cout << "    Worry level ";
		if (operation[1] == "*") {
			newWorryLevel *= op2;
			std::cout << "is multiplied by " << op2 << " to " << newWorryLevel << std::endl;
		} else {
			newWorryLevel += op2;
			std::cout << "increases by " << op2 << " to " << newWorryLevel << std::endl;
		}

		newWorryLevel = newWorryLevel / 3;
		std::cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << newWorryLevel << std::endl;

		if (newWorryLevel % test[0] == 0) {
			std::cout << "    Current worry level is divisible by  " << test[0] << std::endl;
			monkeyItems[test[1]].push(newWorryLevel);
			std::cout << "    Item with worry level " << newWorryLevel << " is thrown to monkey " << test[1] << std::endl;
		} else {
			std::cout << "    Current worry level is not divisible by  " << test[0] << std::endl;
			monkeyItems[test[2]].push(newWorryLevel);
			std::cout << "    Item with worry level " << newWorryLevel << " is thrown to monkey " << test[2] << std::endl;
		}
	}

	monkeyItems[monkeyId] = std::queue<int>();
}

int main() {
	std::map<int, int> monkeyInspections;
	std::map<int, std::queue<int>> monkeyItems;
	std::map<int, std::vector<std::string>> monkeyOperations;
	std::map<int, std::array<int, 3>> monkeyTest;

	const std::regex ranges(R"(Monkey (\d+))");
	std::smatch match1;

	auto monkeyBlocks = Utils::readBlocks("input11.txt");
std::cout << "Found " << monkeyBlocks.size() << " monkeys" << std::endl;
	for (const auto &monkeyBlock: monkeyBlocks) {
		parseMonkey(monkeyBlock, monkeyItems, monkeyOperations, monkeyTest);
	}

	for (int round = 0; round < 20; round++) {
		for (int i = 0; i < monkeyItems.size(); i++) {
			processMonkey(i, monkeyInspections, monkeyItems, monkeyOperations[i], monkeyTest[i]);
		}
	}

	for (auto & monkeyItem : monkeyItems) {
		std::cout << "Monkey " << monkeyItem.first << ": ";
		while(!monkeyItem.second.empty()) {
			std::cout << monkeyItem.second.front() << " ";
			monkeyItem.second.pop();
		}

		std::cout << std::endl;
	}

	std::vector<int> test;
	for (const auto& inspection : monkeyInspections) {
		test.push_back(inspection.second);
		std::cout << "Monkey " << inspection.first << " has inspected " << inspection.second << " items" << std::endl;
	}

	std::sort(test.begin(), test.end(), std::greater());
	std::cout << test[0] * test[1] << std::endl;
}
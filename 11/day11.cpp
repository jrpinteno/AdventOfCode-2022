#include "../Utils/Utils.h"

#include <queue>
#include <regex>
#include <numeric>

struct Monkey {
	static int commonDivisor;

	int id{};
	std::queue<uint64_t> items;
	size_t inspections{0};
	std::function<uint64_t(uint64_t)> operation;
	int divisibleBy{1};
	int successMonkeyId{}, failMonkeyId{};
};

Monkey parseMonkeyBlock(const std::vector<std::string>& monkey) {
	Monkey newMonkey;

	const std::regex monkeyPattern(R"(Monkey (\d+):)");
	std::smatch matchMonkey;
	std::regex_match(monkey[0], matchMonkey, monkeyPattern);
	newMonkey.id = std::stoi(matchMonkey[1].str());

	// ITEMS
	const std::regex itemsPattern(R"(\s+Starting items: (\d+(?:,\s*\d+)*))");
	std::smatch matchItems;
	std::regex_match(monkey[1], matchItems, itemsPattern);
	auto items = matchItems[1].str();

	std::smatch match;
	std::regex regex(R"(\d+)");

	for (std::sregex_iterator it(items.begin(), items.end(), regex), end; it != end; it++) {
		const std::smatch& matchItem = *it;
		newMonkey.items.push(std::stoi(matchItem.str()));
	}

	// OPERATION
	const std::regex operationPattern(R"(\s+Operation: new = (.*))");
	std::smatch matchOperation;
	std::regex_match(monkey[2], matchOperation, operationPattern);
	auto operation = Utils::split(matchOperation[1].str());

	int oper2 = 0;
	bool isSame = false;
	if (operation[2][0] == 'o') {
		isSame = true;
	} else {
		oper2 = std::stoi(operation[2]);
	}

	if (operation[1] == "*") {
		newMonkey.operation = [oper2, isSame](uint64_t old) {
			uint64_t newWorryLevel;
			if (isSame) {
				newWorryLevel = old * old;
			} else {
				newWorryLevel = (old * oper2);
			}

			return newWorryLevel % Monkey::commonDivisor;
		};
	} else {
		newMonkey.operation = [oper2, isSame](uint64_t old) {
			uint64_t newWorryLevel;
			if (isSame) {
				newWorryLevel = old + old;
			} else {
				newWorryLevel = old + oper2;
			}

			return newWorryLevel % Monkey::commonDivisor;
		};
	}

	// TEST
	const std::regex testPattern(R"(\s+Test: divisible by (\d+))");
	std::smatch matchTest;
	std::regex_match(monkey[3], matchTest, testPattern);
	newMonkey.divisibleBy = std::stoi(matchTest[1].str());
	Monkey::commonDivisor = std::lcm(Monkey::commonDivisor, newMonkey.divisibleBy);

	// TRUE CASE
	const std::regex truePattern(R"(\s+If true: throw to monkey (\d+))");
	std::smatch matchTrue;
	std::regex_match(monkey[4], matchTrue, truePattern);
	newMonkey.successMonkeyId = std::stoi(matchTrue[1].str());

	// FALSE CASE
	const std::regex falsePattern(R"(\s+If false: throw to monkey (\d+))");
	std::smatch matchFalse;
	std::regex_match(monkey[5], matchFalse, falsePattern);
	newMonkey.failMonkeyId = std::stoi(matchFalse[1].str());

	return newMonkey;
}

void processMonkey(Monkey& monkey, std::vector<Monkey>& monkeys, int boredom) {
	while(!monkey.items.empty()) {
		monkey.inspections += 1;

		auto item = monkey.items.front();
		monkey.items.pop();

		auto newWorryLevel = monkey.operation(item);

		newWorryLevel = newWorryLevel / boredom;

		if (newWorryLevel % monkey.divisibleBy == 0) {
			monkeys[monkey.successMonkeyId].items.push(newWorryLevel);
		} else {
			monkeys[monkey.failMonkeyId].items.push(newWorryLevel);
		}
	}
}

void makeMonkeysWork(std::vector<Monkey> monkeys, int rounds, int boredom) {
	for (int round = 0; round < rounds; round++) {
		for (int i = 0; i < monkeys.size(); i++) {
			processMonkey(monkeys[i], monkeys, boredom);
		}
	}

	std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& first, const Monkey& second) {
		return first.inspections > second.inspections;
	});

	std::cout << monkeys[0].inspections * monkeys[1].inspections << std::endl;
}

int Monkey::commonDivisor = 1;

int main() {
	std::vector<Monkey> monkeys;
	auto monkeyBlocks = Utils::readBlocks("test");

	for (const auto &monkeyBlock: monkeyBlocks) {
		auto monkey = parseMonkeyBlock(monkeyBlock);
		monkeys.push_back(monkey);
	}

	makeMonkeysWork(monkeys, 20, 3);
	makeMonkeysWork(monkeys, 10000, 1);
}

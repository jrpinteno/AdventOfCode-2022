#include "../Utils/Utils.h"

#include <iostream>
#include <regex>
#include <unordered_map>
#include <variant>

struct Operation {
	Operation(const std::string monkey1, const std::string monkey2, char op) :
		monkey1(monkey1), monkey2(monkey2), op(op) {}

	std::string monkey1;
	std::string monkey2;
	char op;
};

using Yell = std::variant<double, Operation>;
using MonkeyMap = std::unordered_map<std::string, Yell>;

MonkeyMap getMonkeyMap(const std::vector<std::string>& monkeys) {
	std::regex pattern(R"((\w+): (.*))");
	std::smatch match;

	MonkeyMap monkeyMap;

	for (const auto& line : monkeys) {
		std::regex_search(line, match, pattern);
		auto parts = Utils::split(match[2].str());

		Yell yell;
		if (parts.size() > 1) {
			yell = Operation(parts[0], parts[2], parts[1][0]);
		} else {
			yell = std::stod(parts[0]);
		}

		monkeyMap[match[1].str()] = yell;
	}

	return monkeyMap;
}

double getMonkeyYell(MonkeyMap& monkeyMap, const std::string& monkey) {
	auto yell = monkeyMap[monkey];

	if (std::holds_alternative<double>(yell)) {
		return std::get<double>(yell);
	} else {
		auto operation = std::get<Operation>(yell);

		switch (operation.op) {
			case '+':
				return getMonkeyYell(monkeyMap, operation.monkey1) + getMonkeyYell(monkeyMap, operation.monkey2);

			case '*':
				return getMonkeyYell(monkeyMap, operation.monkey1) * getMonkeyYell(monkeyMap, operation.monkey2);

			case '-':
				return getMonkeyYell(monkeyMap, operation.monkey1) - getMonkeyYell(monkeyMap, operation.monkey2);

			case '/':
				return getMonkeyYell(monkeyMap, operation.monkey1) / getMonkeyYell(monkeyMap, operation.monkey2);
		}
	}

	return 0;
}

double findHuman(MonkeyMap& monkeyMap) {
	auto rootOperation = std::get<Operation>(monkeyMap["root"]);
	auto newOperation = Operation(rootOperation.monkey1, rootOperation.monkey2, '-');
	monkeyMap["root"] = newOperation;

	double x1 = 0;
	double x2 = 100000;
	double delta = 0;
	double y2;

	do {
		monkeyMap["humn"] = x2;
		y2 = getMonkeyYell(monkeyMap, "root");

		monkeyMap["humn"] = x1;
		auto temp = x2 - y2 * (x2 - x1)/(y2 - getMonkeyYell(monkeyMap, "root"));
		x1 = x2;
		x2 = temp;
	} while (std::abs(y2) > delta);

	return x2;
}

int main() {
	const auto monkeys = Utils::readLines("input21.txt");
	auto monkeyMap = getMonkeyMap(monkeys);

	std::cout << (long long)getMonkeyYell(monkeyMap, "root") << std::endl;
	std::cout << (long long)findHuman(monkeyMap);
}

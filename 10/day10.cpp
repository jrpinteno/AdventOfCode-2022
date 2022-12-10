#include "../Utils/Utils.h"

#include <iostream>

void drawPixel(int cycle, int xReg) {
	std::cout << (std::abs(xReg - (cycle - 1) % 40) <= 1 ? "#" : ".");
}

void checkEndLine(int cycle) {
	if ((cycle - 1) % 40 == 0) {
		std::cout << std::endl;
	}
}

void updateSignal(int& sumSignals, const int& xReg, const int& cycle) {
	if ((cycle + 20) % 40 == 0) {
		sumSignals += xReg * cycle;
	}
}

int main() {
	auto operations = Utils::readLines("input10.txt");

	auto xReg = 1;
	auto cycle = 1;
	auto sumSignals = 0;

	for (const auto& op : operations) {
		checkEndLine(cycle);
		drawPixel(cycle, xReg);

		if (op[0] == 'a') {
			auto decoded = Utils::split(op);

			cycle += 1;
			checkEndLine(cycle);
			drawPixel(cycle, xReg);
			updateSignal(sumSignals, xReg, cycle);

			cycle += 1;
			xReg += std::stoi(decoded[1]);
		} else if (op[0] == 'n') {
			cycle += 1;
		}

		updateSignal(sumSignals, xReg, cycle);
	}

	std::cout << std::endl;
	std::cout << sumSignals << std::endl;
}

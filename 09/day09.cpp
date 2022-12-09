#include "../Utils/Utils.h"
#include <utility>
#include <iostream>
#include <regex>
#include <set>

using Knot = std::pair<int, int>;
using Position = std::pair<int, int>;

template <typename N>
std::ostream& operator <<(std::ostream& output, const std::pair<N, N>&data) {
	output << "[" << data.first << ", " << data.second << "]";
	return output;
}

bool tailInContact(const Knot& head, const Knot& tail) {
	return std::abs(head.first - tail.first) <= 1 && std::abs(head.second - tail.second) <= 1;
}

void moveKnotIfNeeded(Knot& firstKnot, Knot& secondKnot) {
	// Check tail contact
	if (tailInContact(firstKnot, secondKnot)) {
		return;
	}

	// Check tail position
	// Horizontal
	if (std::abs(firstKnot.first - secondKnot.first) > 1 && firstKnot.second == secondKnot.second) {
		secondKnot.first += (firstKnot.first > secondKnot.first) ? 1 : -1;
	} else if (firstKnot.first == secondKnot.first && std::abs(firstKnot.second - secondKnot.second) > 1) {
		// Vertical
		secondKnot.second += (firstKnot.second > secondKnot.second) ? 1 : -1;
	} else {
		// Diagonal
		secondKnot.first += (firstKnot.first > secondKnot.first) ? 1 : -1;
		secondKnot.second += (firstKnot.second > secondKnot.second) ? 1 : -1;
	}
}

void solve(const std::vector<std::string>& movements, int amountKnots) {
	std::vector<Knot> knots(amountKnots, std::make_pair(0, 0));
	std::set<Position> visited;
	visited.insert({0, 0});

	const std::regex moveSet(R"(([R|U|L|D]) (\d+))");
	std::smatch match;

	for (const auto& line : movements) {
		std::regex_match(line, match, moveSet);
		const auto moveDistance = std::stoi(match[2].str());

		std::pair<int, int> move;

		switch (match[1].str()[0]) {
			case 'R':
				move = {0, 1};
				break;

			case 'U':
				move = {1, 0};
				break;

			case 'L': {
				move = {0, -1};
				break;
			}

			case 'D':
				move = {-1, 0};
				break;
		}

		for (int i = 0; i < moveDistance; i++) {
			// Move head
			knots[0].first += move.first;
			knots[0].second += move.second;

			for (int j = 1; j < knots.size(); j++) {
				moveKnotIfNeeded(knots[j - 1], knots[j]);
			}

			visited.insert(knots.back());
		}
	}

	std::cout << visited.size() << std::endl;
}

int main() {
	auto movements = Utils::readLines("input09.txt");

	solve(movements, 2);
	solve(movements, 10);
}

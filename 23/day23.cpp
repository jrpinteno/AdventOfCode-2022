#include "../Utils/Utils.h"

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <queue>

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const noexcept {
		std::size_t h1 = std::hash<T1>{}(pair.first);
		std::size_t h2 = std::hash<T2>{}(pair.second);

		return h1 ^ (h2 << 1);
	}

	//friend std::ostream &operator<<(std::ostream &os, const pair_hash &hash);
};

std::pair<int, int> operator+(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
	return { lhs.first + rhs.first, lhs.second + rhs.second};
}

using Direction = std::pair<int, int>;

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& pair) {
	os << "[" << pair.first << ", " << pair.second << "]";
	return os;
}

using Directions = std::unordered_map<std::string, Direction>;
using Elf = std::pair<int, int>;
using Grid = std::unordered_set<Elf, pair_hash>;
using ProposedMoves = std::unordered_map<Direction, std::vector<Elf>, pair_hash>;

struct DirectionCheck {
	DirectionCheck(std::string  direction1, std::string  direction2, std::string  direction3)
			: direction1(std::move(direction1)), direction2(std::move(direction2)), direction3(std::move(direction3)) {}

	std::string direction1;
	std::string direction2;
	std::string direction3;
};

static Directions directions {
		{ "N", Direction { -1, 0 } },
		{ "NE", Direction { -1, 1 } },
		{ "E", Direction { 0, 1 } },
		{ "SE", Direction { 1, 1 } },
		{ "S", Direction { 1, 0 } },
		{ "SW", Direction { 1, -1 } },
		{ "W", Direction { 0, -1 } },
		{ "NW", Direction { -1, -1 } }
};

static std::deque<std::pair<std::string, DirectionCheck>> directionChecks = {
		{ "N", DirectionCheck("NW", "N", "NE") },
		{ "S", DirectionCheck("SE", "S", "SW") },
		{ "W", DirectionCheck("SW", "W", "NW") },
		{ "E", DirectionCheck("NE", "E", "SE") },
};

Grid fillGrid(const std::vector<std::string>& gridLines) {
	Grid elves;

	for (int i = 0; i < gridLines.size(); ++i) {
		for (int j = 0; j < gridLines[i].size(); ++j) {
			if (gridLines[i][j] == '#') {
				elves.insert({ i, j });
			}
		}
	}

	return elves;
}

bool isDirectionOccupied(const Grid& elves, const Elf& elf, std::string direction) {
	return elves.count(elf + directions[direction]) > 0;
}

bool canMove(const Grid& elves, const Elf& elf, const DirectionCheck& directionCheck) {
	return !isDirectionOccupied(elves, elf, directionCheck.direction1) &&
			!isDirectionOccupied(elves, elf, directionCheck.direction2) &&
			!isDirectionOccupied(elves, elf, directionCheck.direction3);
}

ProposedMoves proposedMoves(Grid& elves) {
	ProposedMoves moves;

	for (const auto& elf : elves) {
		bool someAdjacent = false;

		for (const auto& direction : directions) {
			someAdjacent |= isDirectionOccupied(elves, elf, direction.first);
		}

		if (!someAdjacent) {
			continue;
		}

		for (const auto& directionCheck : directionChecks) {
			if (canMove(elves, elf, directionCheck.second)) {
				moves[directions[directionCheck.first] + elf].emplace_back(elf);
				break;
			}
		}
	}

	auto temp = directionChecks.front();
	directionChecks.pop_front();
	directionChecks.emplace_back(temp);

	return moves;
}

std::pair<Elf, Elf> getBoundingBox(const Grid& elves) {
	Elf minCube = { INT_MAX, INT_MAX };
	Elf maxCube { INT_MIN, INT_MIN };

	for (const auto& cube : elves) {
		minCube = {
				std::min(std::get<0>(minCube), std::get<0>(cube)),
				std::min(std::get<1>(minCube), std::get<1>(cube))
		};

		maxCube = {
				std::max(std::get<0>(maxCube), std::get<0>(cube)),
				std::max(std::get<1>(maxCube), std::get<1>(cube))
		};
	}

	return { minCube, maxCube };
}

int main() {
	auto gridLines = Utils::readLines("testBig");
	auto elves = fillGrid(gridLines);

	auto moves = proposedMoves(elves);
	int j = 1;
	while (!moves.empty()) {
		for (const auto &proposedMove: moves) {
			if (proposedMove.second.size() > 1) {
				continue;
			}

			elves.erase(proposedMove.second[0]);
			elves.insert(proposedMove.first);
		}

		moves = proposedMoves(elves);
		j += 1;
	}

	auto boundingBox = getBoundingBox(elves);
	auto height = boundingBox.second.first - boundingBox.first.first + 1;
	auto width = boundingBox.second.second - boundingBox.first.second + 1;

	std::cout << "Empty spaces: " << height * width - elves.size() << std::endl;
	std::cout << "Stops after " << j << " rounds" << std::endl;
}

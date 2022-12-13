#include "../Utils/Utils.h"

#include <queue>
#include <set>
#include <utility>

using Grid = std::vector<std::vector<char>>;
using Coordinate = std::pair<int, int>;
using Move = std::pair<int, int>;

struct Square {
	Square(Coordinate pos, int dist) : position(std::move(pos)), distance(dist) {}

	Coordinate position;
	int distance{};
};

std::array<Move, 4> moves({
	std::make_pair(1, 0),
	std::make_pair(-1, 0),
	std::make_pair(0, 1),
	std::make_pair(0, -1)
});

std::vector<Coordinate> startingPoints;

std::pair<Coordinate, Coordinate> locateStartEnd(Grid& grid) {
	Coordinate start;
	Coordinate end;

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (grid[i][j] == 'S') {
				start = { i, j };
				grid[i][j] = 'a';
			} else if (grid[i][j] == 'E') {
				end = { i, j };
				grid[i][j] = 'z';
			}

			if (grid[i][j] == 'a') {
				startingPoints.emplace_back( i, j );
			}
		}
	}

	return { start, end };
}

bool canClimb(const Grid& grid, Coordinate position, Move move) {
	auto currentStep = grid[position.first][position.second];
	auto nextStep = grid[position.first + move.first][position.second + move.second];

	return nextStep - currentStep <= 1;
}

bool moveIsContained(const Grid& grid, const Coordinate& position, const Move& move) {
	auto yMove = position.first + move.first;
	auto xMove = position.second + move.second;

	return yMove >= 0 && yMove < grid.size() &&
		xMove >= 0 && xMove < grid.front().size();
}

size_t findPath(const Grid& grid, const Square& start, const Square& goal) {
	std::queue<Square> openSet;
	openSet.push(start);
	std::set<Coordinate> visited;

	while (!openSet.empty()) {
		auto current = openSet.front();
		openSet.pop();

		if (current.position == goal.position) {
			return current.distance;
		}

		if (visited.find(current.position) != visited.end()) {
			continue;
		}

		visited.insert(current.position);

		// Find neighbours
		for (const auto& move : moves) {
			if (moveIsContained(grid, current.position, move) && canClimb(grid, current.position, move)) {
				auto newSquare = Square({current.position.first + move.first, current.position.second + move.second}, current.distance + 1);

				openSet.push(newSquare);
			}
		}
	}

	return SIZE_T_MAX;
}

void part01(const Grid& charGrid, const Square& start, const Square& goal) {
	std::cout << findPath(charGrid, start, goal) << std::endl;
}

void part02(const Grid& charGrid, const Square& goal) {
	auto distance = SIZE_T_MAX;

	for (const auto& starter : startingPoints) {
		distance = std::min(distance, findPath(charGrid, Square(starter, 0), goal));
	}

	std::cout << distance << std::endl;
}

int main() {
	auto charGrid = Utils::readGrid("input12.txt");
	auto squares = locateStartEnd(charGrid);
	auto start = Square(squares.first, 0);
	auto end = Square(squares.second, 0);

	part01(charGrid, start, end);
	part02(charGrid, end);
}


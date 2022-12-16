//
// Created by Xavi R. Pinteño on 14.12.2022.
//

#include "../Utils/Utils.h"

#include <array>
#include <map>
#include <regex>

using SandMove = std::pair<int, int>;
using Coordinate = std::pair<int, int>;

std::pair<int, int> operator+(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
	return { lhs.first + rhs.first, lhs.second + rhs.second};
}

template <typename N>
std::ostream& operator <<(std::ostream& output, const std::pair<N, N>&data) {
	output << "[" << data.first << ", " << data.second << "]";
	return output;
}

std::array<SandMove, 3> sandMoves {
	std::make_pair(0, 1), // Move down
	std::make_pair(-1, 1), // Move diagonally left
	std::make_pair(1, 1), // Move diagonally right
};

std::vector<Coordinate> parsePath(const std::string& path) {
	std::string delimiter = " -> ";
	size_t start = 0;
	size_t next;

	const std::regex movement(R"((\d+),(\d+))");
	std::smatch match;

	std::vector<Coordinate> rockPath;

	while ((next = path.find(delimiter, start)) != std::string::npos) {
		auto coordinate = path.substr(start, next - start);
		std::regex_match(coordinate, match, movement);

		int a = std::stoi(match[1].str());
		int b = std::stoi(match[2].str());

		start = next + delimiter.size();
		rockPath.emplace_back( a, b);
	}

	auto coordinate = path.substr(start);
	std::regex_match(coordinate, match, movement);

	int a = std::stoi(match[1].str());
	int b = std::stoi(match[2].str());

	rockPath.emplace_back( a, b);

	return rockPath;
}

int plantRocks(std::map<Coordinate, char>& structure, const std::string& path) {
	auto rockPath = parsePath(path);
	int maxY = rockPath[0].second;

	for (int i = 0; i < rockPath.size() - 1; i++) {
		maxY = std::max(maxY, rockPath[i + 1].second);
		if (rockPath[i].first == rockPath[i + 1].first) {
			if (rockPath[i].second < rockPath[i + 1].second) {
				for (int start = rockPath[i].second; start <= rockPath[i + 1].second; start++) {
					auto rock = std::make_pair(rockPath[i].first, start);

					structure[rock] = '#';
				}
			} else {
				for (int start = rockPath[i].second; start >= rockPath[i + 1].second; start--) {
					structure[{rockPath[i].first, start}] = '#';
				}
			}
		} else {
			if (rockPath[i].first < rockPath[i + 1].first) {
				for (int start = rockPath[i].first; start <= rockPath[i + 1].first; start++) {
					structure[{start, rockPath[i].second}] = '#';
				}
			} else {
				for (int start = rockPath[i].first; start >= rockPath[i + 1].first; start--) {
					structure[{start, rockPath[i].second}] = '#';
				}
			}
		}
	}

	return maxY;
}

bool canMove(std::map<Coordinate, char>& structure, const Coordinate& sandPosition, const SandMove& move) {
	return structure.count(sandPosition + move) == 0;
}

int sandFall(std::map<Coordinate, char>& structure) {
	Coordinate sandGrain = { 500, 0 };

	bool comesToRest = false;

	while (!comesToRest) {
		auto down = SandMove { 0, 1 };
		if (canMove(structure, sandGrain, down)) {
			sandGrain = sandGrain + down;
			continue;
		}

		// Grain will move to the left and fall
		if (sandGrain.first == structure.begin()->first.first) {
			return 0;
		}

		auto downLeft = SandMove { -1, 1 };
		if (canMove(structure, sandGrain, downLeft)) {
			sandGrain = sandGrain + downLeft;
			continue;
		}

		// Grain will move to the right and fall
		if (sandGrain.first == structure.rbegin()->first.first) {
			return 0;
		}

		auto downRight = SandMove { 1, 1 };
		if (canMove(structure, sandGrain, downRight)) {
			sandGrain = sandGrain + downRight;
			continue;
		}

		comesToRest = true;
		structure[sandGrain] = 'o';
	}

	return 1;
}

int sandFall2(std::map<Coordinate, char>& structure, int maxY) {
	Coordinate sandGrain = { 500, 0 };

	bool comesToRest = false;

	if (structure.count(std::make_pair(500, 0)) != 0) {
		return 0;
	}

	while (!comesToRest) {
		auto down = SandMove { 0, 1 };
		if (canMove(structure, sandGrain, down) && sandGrain.second < maxY + 1) {
			sandGrain = sandGrain + down;
			continue;
		}

		auto downLeft = SandMove { -1, 1 };
		if (canMove(structure, sandGrain, downLeft) && sandGrain.second < maxY + 1) {
			sandGrain = sandGrain + downLeft;
			continue;
		}

		auto downRight = SandMove { 1, 1 };
		if (canMove(structure, sandGrain, downRight) && sandGrain.second < maxY + 1) {
			sandGrain = sandGrain + downRight;
			continue;
		}

		comesToRest = true;
		structure[sandGrain] = 'o';
	}

	return 1;
}

int main() {
	std::map<Coordinate, char> reservoir;
	auto rockFormations = Utils::readLines("input14.txt");

	int maxY = 0;
	for (const std::string& rockFormation : rockFormations) {
		maxY = std::max(plantRocks(reservoir, rockFormation), maxY);
	}

	int sandGrains = 0;
	while (sandFall(reservoir) == 1) {
		sandGrains += 1;
	}

	std::cout << sandGrains << std::endl;

	sandGrains = 0;
	while (sandFall2(reservoir, maxY) == 1) {
		sandGrains += 1;
	}

	std::cout << sandGrains << std::endl;
}
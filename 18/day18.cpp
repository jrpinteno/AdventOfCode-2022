#include "../Utils/Utils.h"

#include <iostream>
#include <unordered_set>
#include <set>
#include <regex>
#include <array>
#include <queue>

using Cube = std::tuple<int, int, int>;
using Lattice = std::set<Cube>;
using Direction = std::tuple<int, int, int>;

constexpr static auto directions = std::array<Direction, 6> {
		Direction { 1, 0, 0 },
		Direction { -1, 0, 0 },
		Direction { 0, 1, 0 },
		Direction { 0, -1, 0 },
		Direction { 0, 0, 1 },
		Direction { 0, 0, -1 }
};

Cube operator+(const Cube& lhs, const Direction& rhs) {
	return {
		std::get<0>(lhs) + std::get<0>(rhs),
		std::get<1>(lhs) + std::get<1>(rhs),
		std::get<2>(lhs) + std::get<2>(rhs)
	};
}

std::array<Cube, 6> neighbours(const Cube& cube) {
	return {
		cube + directions[0],
		cube + directions[1],
		cube + directions[2],
		cube + directions[3],
		cube + directions[4],
		cube + directions[5]
	};
}

Lattice fillLattice(const std::vector<std::string>& cubes) {
	Lattice lattice;
	const std::regex coordinates(R"((\d+),(\d+),(\d+))");
	std::smatch match;

	for (const auto& cubeString : cubes) {
		std::regex_match(cubeString, match, coordinates);

		Cube cube = {
				std::stoi(match[1].str()),
				std::stoi(match[2].str()),
				std::stoi(match[3].str())};

		lattice.insert(cube);
	}

	return lattice;
}

std::pair<Cube, Cube> boundingBox(const Lattice& lattice) {
	Cube minCube = { INT_MAX, INT_MAX, INT_MAX };
	Cube maxCube { INT_MIN, INT_MIN, INT_MIN };

	for (const auto& cube : lattice) {
		minCube = {
			std::min(std::get<0>(minCube), std::get<0>(cube)),
			std::min(std::get<1>(minCube), std::get<1>(cube)),
			std::min(std::get<2>(minCube), std::get<2>(cube))
		};

		maxCube = {
				std::max(std::get<0>(maxCube), std::get<0>(cube)),
				std::max(std::get<1>(maxCube), std::get<1>(cube)),
				std::max(std::get<2>(maxCube), std::get<2>(cube))
		};
	}

	return { minCube, maxCube };
}

bool inBoundingBox(const Cube& cube, const Cube& minCube, const Cube& maxCube) {
	return
		std::get<0>(cube) >= std::get<0>(minCube) - 1 && std::get<0>(cube) <= std::get<0>(maxCube) + 1 &&
		std::get<1>(cube) >= std::get<1>(minCube) - 1 && std::get<1>(cube) <= std::get<1>(maxCube) + 1 &&
		std::get<2>(cube) >= std::get<2>(minCube) - 1 && std::get<2>(cube) <= std::get<2>(maxCube) + 1;
}

size_t flood(const Lattice& lattice) {
	const auto [minCube, maxCube] = boundingBox(lattice);

	std::queue<Cube> openSet;
	openSet.push(minCube);
	std::set<Cube> visited;

	size_t sum = 0;

	while (!openSet.empty()) {
		auto cube = openSet.front();
		openSet.pop();

		if (visited.find(cube) != visited.end()) {
			continue;
		}

		visited.insert(cube);

		for (const auto& neighbour : neighbours(cube)) {
			if (!inBoundingBox(neighbour, minCube, maxCube)) {
				continue;
			}

			if (visited.find(neighbour) != visited.end()) {
				continue;
			}

			if (lattice.find(neighbour) != lattice.end()) {
				sum += 1;
				continue;
			}

			openSet.push(neighbour);
		}
	}

	return sum;
}

int main() {
	auto input = Utils::readLines("input18.txt");
	auto lattice = fillLattice(input);

	int sum = 0;
	for (const auto& cube : lattice) {
		for (const auto& neighbour : neighbours(cube)) {
			sum += lattice.find(neighbour) == lattice.end();
		}
	}

	std::cout << sum << std::endl;
	std::cout << flood(lattice) << std::endl;
}

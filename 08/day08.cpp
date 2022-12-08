#include "../Utils/Utils.h"
#include <iostream>

std::pair<bool, int> checkLeft(const std::vector<std::vector<int>>& trees, std::pair<int, int> treePosition) {
	size_t treeSight = 0;

	for (int j = treePosition.second - 1; j >= 0; --j) {
		if (trees[treePosition.first][j] >= trees[treePosition.first][treePosition.second]) {
			return {false, treePosition.second - j };
		}

		treeSight += 1;
	}

	return {true, treeSight };
}

std::pair<bool, int> checkRight(const std::vector<std::vector<int>>& trees, std::pair<int, int> treePosition) {
	size_t treeSight = 0;

	for (int j = treePosition.second + 1; j < trees.size(); j++) {
		if (trees[treePosition.first][j] >= trees[treePosition.first][treePosition.second]) {
			return {false, j - treePosition.second };
		}

		treeSight += 1;
	}

	return {true, treeSight };
}

std::pair<bool, int> checkTop(const std::vector<std::vector<int>>& trees, std::pair<int, int> treePosition) {
	size_t treeSight = 0;

	for (int i = treePosition.first - 1; i >= 0; --i) {
		if (trees[i][treePosition.second] >= trees[treePosition.first][treePosition.second]) {
			return {false, treePosition.first - i };
		}

		treeSight += 1;
	}

	return {true, treeSight };
}

std::pair<bool, int> checkBottom(const std::vector<std::vector<int>>& trees, std::pair<int, int> treePosition) {
	size_t treeSight = 0;

	for (int i = treePosition.first + 1; i < trees.size(); i++) {
		if (trees[i][treePosition.second] >= trees[treePosition.first][treePosition.second]) {
			return {false, i - treePosition.first };
		}

		treeSight += 1;
	}

	return {true, treeSight };
}

int main() {
	const auto grid = Utils::readIntGrid("input08.txt");

	auto sum = 0;
	auto scenicScore = 0;

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid.size(); j++) {
			auto left = checkLeft(grid, {i, j});
			auto right = checkRight(grid, {i, j});
			auto top = checkTop(grid, {i, j});
			auto bottom = checkBottom(grid, {i, j});

			if (left.first || top.first || right.first || bottom.first) {
				sum += 1;
			}

			scenicScore = std::max(scenicScore, left.second * top.second * right.second * bottom.second);
		}
	}

	std::cout << sum << std::endl;
	std::cout << scenicScore << std::endl;
}
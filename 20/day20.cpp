#include "../Utils/Utils.h"

#include <algorithm>
#include <iostream>
#include <list>

using NumPair = std::pair<std::list<int>::size_type, long long>;

long long rem_euclid(long long x, long long y) {
	int64_t r = x % y;
	if (r < 0) {
		r += y;
	}

	return r;
}

void mix(const std::vector<int>& encryptedFile, int iterations, long long key) {
	std::list<NumPair> list;

	for (std::list<int>::size_type i = 0; i < encryptedFile.size(); ++i) {
		list.emplace_back(i, encryptedFile[i] * key);
	}

	std::list<NumPair> mutableCopy = list;

	for (int i = 0; i < iterations; ++i) {
		for (const auto& pair: list) {
			auto it = std::find(mutableCopy.begin(), mutableCopy.end(), pair);
			auto index = std::distance(mutableCopy.begin(), it);

			auto temp = *std::next(mutableCopy.begin(), index);
			mutableCopy.erase(it);
			auto listSize = mutableCopy.size();
			long long movePosition = rem_euclid(index + temp.second, listSize);

			movePosition = movePosition == 0 ? listSize : movePosition;

			mutableCopy.emplace(std::next(mutableCopy.begin(), movePosition) ,temp);
		}
	}

	auto it = std::find_if(mutableCopy.begin(), mutableCopy.end(),[&](const auto& pair){
		return pair.second == 0;
	});

	auto zeroIndex = std::distance(mutableCopy.begin(), it);

	auto p1000 = *std::next(mutableCopy.begin(), ((zeroIndex + 1000) % mutableCopy.size()));
	auto p2000 = *std::next(mutableCopy.begin(), ((zeroIndex + 2000) % mutableCopy.size()));
	auto p3000 = *std::next(mutableCopy.begin(), ((zeroIndex + 3000) % mutableCopy.size()));

	std::cout << p1000.second + p2000.second + p3000.second << std::endl;
}

int main() {
	auto encryptedFile = Utils::readIntLines("input20.txt");

	mix(encryptedFile, 1, 1);
	mix(encryptedFile, 10, 811589153);
}

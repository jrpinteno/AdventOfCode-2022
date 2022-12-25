#include "../Utils/Utils.h"

char decToSnafu(const int64_t digit) {
	const std::array<char, 5> snafu{'0', '1', '2', '=', '-'};
	return snafu[digit];
}

int main() {
	auto snafus = Utils::readLines("input25.txt");

	int64_t snafuSum = 0;

	for (auto& snafu : snafus) {
		int64_t power = 1;

		std::string::reverse_iterator rit = snafu.rbegin();

		while (rit != snafu.rend()) {
			switch (*rit) {
				case '2':
					snafuSum += 2 * power;
					break;

				case '1':
					snafuSum += power;
					break;

				case '0':
					snafuSum += 0;
					break;

				case '-':
					snafuSum -= power;
					break;

				case '=':
					snafuSum -= 2 * power;
					break;
			}

			power *= 5;
			rit += 1;
		}
	}

	std::string result{};

	while (snafuSum > 0) {
		auto digit = snafuSum % 5;

		result += decToSnafu(digit);

		if (digit > 2) {
			snafuSum += 5;
		}

		snafuSum /= 5;
	}

	std::reverse(result.begin(), result.end());
	std::cout <<  result << std::endl;
}

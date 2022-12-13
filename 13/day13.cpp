#include "../Utils/Utils.h"

#include <iostream>
#include <variant>
#include <charconv>

struct Packet : std::variant<int, std::vector<Packet>> {
	using List = std::vector<Packet>;

	using variant::variant;
	explicit Packet(int number) : variant(number) { }
	explicit Packet(const List& list) : variant(list) { }

	friend bool operator<(const Packet& lhs, const Packet& rhs) {
		if (std::holds_alternative<int>(lhs) && std::holds_alternative<int>(rhs)) {
			std::cout << "Two ints: Comparing " << std::get<int>(lhs) << " < " << std::get<int>(rhs) << std::endl;
			return std::get<int>(lhs) < std::get<int>(rhs);
		}

		if (std::holds_alternative<List>(lhs) && std::holds_alternative<List>(rhs)) {
			std::cout << "Two lists" << std::endl;
			auto lhsList = std::get<List>(lhs);
			auto rhsList = std::get<List>(rhs);

			if (lhsList.empty()) {
				std::cout << " - First list empty: right" << std::endl;
				return true;
			}

			if (rhsList.empty()) {
				std::cout << " - Second list empty: wrong" << std::endl;
				return false;
			}

			return std::lexicographical_compare(lhsList.begin(), lhsList.end(), rhsList.begin(), rhsList.end());
		}

		if (std::holds_alternative<int>(lhs)) {
			return List { std::get<int>(lhs) } < rhs;
		}

		if (std::holds_alternative<int>(rhs)) {
			return lhs < List { std::get<int>(rhs) };
		}

		return false;
	}
};

auto parse(std::string_view& text) -> Packet {
	// Empty
	if (text[0] == '[' && text[1] == ']') {
		return Packet::List {};
	}

	if (text[0] == '[') {
		Packet::List list;

		while(text[0] != ']') {
			text.remove_prefix(1);
			list.emplace_back(parse(text));
		}

		text.remove_prefix(1);

		return list;
	}

	int value;
	auto result = std::from_chars(text.data(), text.data() + text.size(), value);
	text.remove_prefix(result.ptr - text.data());

	return value;
}

Packet parse(const std::string& text) {
	std::string_view sv = text;
	return parse(sv);
}

bool processPair(const std::string& left, const std::string& right) {
	std::cout << left << std::endl;
	std::cout << right << std::endl;

	auto lhs = parse(left);
	auto rhs = parse(right);

	return lhs < rhs;
}

int main() {
	auto pairs = Utils::readBlocks("test");

	int i = 1;
	int sum = 0;
	for (const auto& pair : pairs) {
		auto right = processPair(pair[0], pair[1]);

		sum += (right ? i : 0);
		i += 1;
	}

	std::cout << sum << std::endl;
}

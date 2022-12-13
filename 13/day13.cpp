#include "../Utils/Utils.h"

#include <iostream>
#include <variant>
#include <charconv>

struct Packet : std::variant<int, std::vector<Packet>> {
	using List = std::vector<Packet>;

	using variant::variant;
	explicit Packet(int number) : variant(number) { }
	explicit Packet(const List& list) : variant(list) { }

	friend bool operator<(const Packet& lhs, const Packet& rhs);
	/*friend bool operator<(const Packet& lhs, const Packet& rhs) {
		if (std::holds_alternative<int>(lhs) && std::holds_alternative<int>(rhs)) {
			return std::get<int>(lhs) < std::get<int>(rhs);
		}

		if (std::holds_alternative<List>(lhs) && std::holds_alternative<List>(rhs)) {
			auto lhsList = std::get<List>(lhs);
			auto rhsList = std::get<List>(rhs);

			return std::lexicographical_compare(lhsList.begin(), lhsList.end(), rhsList.begin(), rhsList.end());
		}

		if (std::holds_alternative<int>(lhs)) {
			return List { std::get<int>(lhs) } < rhs;
		}

		if (std::holds_alternative<int>(rhs)) {
			return lhs < List { std::get<int>(rhs) };
		}

		return false;
	}*/
};


struct PacketVisitor {
	bool operator()(int lhs, int rhs) const {
		return lhs < rhs;
	}

	bool operator()(Packet::List const& lhs, Packet::List const& rhs) const {
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	bool operator()(int lhs, Packet::List const& rhs) const {
		return (*this)(Packet::List{lhs}, rhs);
	}

	bool operator()(Packet::List const& lhs, int rhs) const {
		return (*this)(lhs, Packet::List{rhs});
	}
};

bool operator<(const Packet& lhs, const Packet& rhs) {
	return std::visit(PacketVisitor {}, lhs, rhs);
}


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

int main() {
	auto pairs = Utils::readBlocks("input13.txt");

	int i = 1;
	int sum = 0;
	std::vector<Packet> packets;

	for (const auto& pair : pairs) {
		auto lhs = parse(pair[0]);
		auto rhs = parse(pair[1]);
		packets.push_back(lhs);
		packets.push_back(rhs);

		sum += (lhs < rhs ? i : 0);
		i += 1;
	}

	std::cout << sum << std::endl;

	Packet packet2 = parse("[[2]]");
	Packet packet6 = parse("[[6]]");

	packets.push_back(packet2);
	packets.push_back(packet6);
	std::sort(packets.begin(), packets.end());

	auto pos2 = std::lower_bound(packets.begin(), packets.end(), packet2);
	auto pos6 = std::lower_bound(pos2, packets.end(), packet6);
	std::cout << (std::distance(packets.begin(), pos2) + 1) * (std::distance(packets.begin(), pos6) + 1) << std::endl;
}

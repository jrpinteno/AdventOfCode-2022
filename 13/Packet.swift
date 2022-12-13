enum Packet {
	case number(Int)
	case list([Packet])
}

extension Packet: Comparable {
	static func < (lhs: Packet, rhs: Packet) -> Bool {
		switch (lhs, rhs) {
			case (.number(let lhsInt), .number(let rhsInt)):
				return lhsInt < rhsInt

			case (.list(let lhsList), .list(let rhsList)):
				return lhsList.lexicographicallyPrecedes(rhsList)

/*
				if lhsList.isEmpty {
					return true
				}

				if rhsList.isEmpty {
					return false
				}

				let zippedArray = zip(lhsList, rhsList)
				for (leftElement, rightElement) in zippedArray {
					if leftElement < rightElement {
						return true
					}
				}

				if lhsList.count < rhsList.count {
					return true
				}

				return false
*/
			case (.number(let lhsInt), _):
				return Packet.list([Packet.number(lhsInt)]) < rhs

			case (_, .number(let rhsInt)):
				return lhs < Packet.list([Packet.number(rhsInt)])
		}
	}
}

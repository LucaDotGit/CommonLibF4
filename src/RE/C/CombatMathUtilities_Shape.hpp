#pragma once

namespace RE::CombatMathUtilities
{
	class Shape
	{
	public:
		// members
		std::uint16_t id;	// 0x00
		std::uint8_t type;	// 0x02
		std::uint8_t flags; // 0x03
	};

	static_assert(sizeof(Shape) == 0x04);
}

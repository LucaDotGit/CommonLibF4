#pragma once

namespace RE::CombatMathUtilities
{
	class Shape
	{
	public:
		// members
		std::uint16_t id;	// 00
		std::uint8_t type;	// 02
		std::uint8_t flags; // 03
	};
	static_assert(sizeof(Shape) == 0x04);
}

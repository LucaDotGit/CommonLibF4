#pragma once

namespace RE
{
	class ScePadTouch
	{
	public:
		// members
		std::uint16_t x;					 // 00
		std::uint16_t y;					 // 02
		std::uint8_t id;					 // 04
		std::array<std::uint8_t, 3> reserve; // 05
	};
	static_assert(sizeof(ScePadTouch) == 0x08);
}

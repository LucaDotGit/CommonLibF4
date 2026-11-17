#pragma once

namespace RE
{
	class ScePadTouch
	{
	public:
		// members
		std::uint16_t x;					 // 0x00
		std::uint16_t y;					 // 0x02
		std::uint8_t id;					 // 0x04
		std::array<std::uint8_t, 3> reserve; // 0x05
	};

	static_assert(sizeof(ScePadTouch) == 0x08);
}

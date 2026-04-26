#pragma once

namespace RE
{
	class ScePadAnalogButtons
	{
	public:
		// members
		std::uint8_t l2;					 // 00
		std::uint8_t r2;					 // 01
		std::array<std::uint8_t, 2> padding; // 02
	};
	static_assert(sizeof(ScePadAnalogButtons) == 0x04);
}

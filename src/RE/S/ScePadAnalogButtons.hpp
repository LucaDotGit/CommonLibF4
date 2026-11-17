#pragma once

namespace RE
{
	class ScePadAnalogButtons
	{
	public:
		// members
		std::uint8_t l2;					 // 0x00
		std::uint8_t r2;					 // 0x01
		std::array<std::uint8_t, 2> padding; // 0x02
	};

	static_assert(sizeof(ScePadAnalogButtons) == 0x04);
}

#pragma once

namespace RE
{
	class ScePadAnalogStick
	{
	public:
		// members
		std::uint8_t x; // 00
		std::uint8_t y; // 01
	};
	static_assert(sizeof(ScePadAnalogStick) == 0x02);
}

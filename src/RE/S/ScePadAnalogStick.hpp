#pragma once

namespace RE
{
	class ScePadAnalogStick
	{
	public:
		// members
		std::uint8_t x; // 0x00
		std::uint8_t y; // 0x01
	};

	static_assert(sizeof(ScePadAnalogStick) == 0x02);
}

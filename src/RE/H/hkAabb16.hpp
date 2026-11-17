#pragma once

namespace RE
{
	class hkAabb16
	{
	public:
		// members
		std::array<std::uint16_t, 3> min; // 0x00
		std::uint16_t key;				  // 0x06
		std::array<std::uint16_t, 3> max; // 0x08
		std::uint16_t key01;			  // 0x0E
	};

	static_assert(sizeof(hkAabb16) == 0x10);
}

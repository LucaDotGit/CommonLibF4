#pragma once

namespace RE
{
	class hkAabb16
	{
	public:
		// members
		std::array<std::uint16_t, 3> min; // 00
		std::uint16_t key;				  // 06
		std::array<std::uint16_t, 3> max; // 08
		std::uint16_t key01;			  // 0E
	};
	static_assert(sizeof(hkAabb16) == 0x10);
}

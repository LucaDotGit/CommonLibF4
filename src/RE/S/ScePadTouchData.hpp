#pragma once

#include "RE/S/ScePadTouch.hpp"

namespace RE
{
	class ScePadTouchData
	{
	public:
		// members
		std::uint8_t touchNum;				 // 0x00
		std::array<std::uint8_t, 7> reserve; // 0x01
		std::array<ScePadTouch, 2> touch;	 // 0x08
	};

	static_assert(sizeof(ScePadTouchData) == 0x18);
}

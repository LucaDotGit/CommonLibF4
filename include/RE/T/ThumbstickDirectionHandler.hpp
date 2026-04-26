#pragma once

#include "RE/D/DIRECTION_VAL.hpp"

namespace RE
{
	class ThumbstickDirectionHandler
	{
	public:
		// members
		REX::Float32 repeatTimer;							   // 00
		REX::Float32 longRepeatRate;						   // 04
		REX::Float32 shortRepeatRate;						   // 08
		REX::Enum<DIRECTION_VAL, std::int32_t> eastPressedDir; // 0C
		std::uint32_t numRepeats;							   // 10
		REX::Float32 heldTime;								   // 14
		bool repeat;										   // 18
		bool debounce;										   // 19
	};
	static_assert(sizeof(ThumbstickDirectionHandler) == 0x1C);
}

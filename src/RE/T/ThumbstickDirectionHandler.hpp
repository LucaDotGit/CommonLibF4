#pragma once

#include "RE/D/DIRECTION_VAL.hpp"

namespace RE
{
	class ThumbstickDirectionHandler
	{
	public:
		// members
		REX::Float32 repeatTimer;							   // 0x00
		REX::Float32 longRepeatRate;						   // 0x04
		REX::Float32 shortRepeatRate;						   // 0x08
		REX::Enum<DIRECTION_VAL, std::int32_t> eastPressedDir; // 0x0C
		std::uint32_t numRepeats;							   // 0x10
		REX::Float32 heldTime;								   // 0x14
		bool repeat;										   // 0x18
		bool debounce;										   // 0x19
	};

	static_assert(sizeof(ThumbstickDirectionHandler) == 0x1C);
}

#pragma once

namespace RE
{
	enum class COVER_TYPE : std::uint32_t
	{
		None = 0,
		Ledge = 1,
		Crouch = 2,
		Partial = 2,
		VeryLow = 4,
		Narrow = 3,
		Low = 4,
		Full = 4,
		Mid = 5,
		High = 6,

		_Count = 7,

		TypeMask = 0xFF'FFFF,

		DirectionLeft = 0x4000'0000,
		DirectionRight = 0x8000'0000,
		DirectionMask = 0xC000'0000
	};
}

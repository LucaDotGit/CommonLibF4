#pragma once

namespace RE
{
	enum class COVER_TYPE : std::uint32_t
	{
		kNone = 0,
		kLedge = 1,
		kCrouch = 2,
		kPartial = 2,
		kVeryLow = 4,
		kNarrow = 3,
		kLow = 4,
		kFull = 4,
		kMid = 5,
		kHigh = 6,

		kTotal = 7,

		kTypeMask = 0xFFFFFF,

		kDirectionLeft = 0x40000000,
		kDirectionRight = 0x80000000,
		kDirectionMask = 0xC0000000
	};
}

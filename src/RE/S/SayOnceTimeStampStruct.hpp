#pragma once

namespace RE
{
	class SayOnceTimeStampStruct
	{
	public:
		// members
		std::uint32_t date; // 0x00
		REX::Float32 hour;	// 0x04
	};

	static_assert(sizeof(SayOnceTimeStampStruct) == 0x08);
}

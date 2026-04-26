#pragma once

namespace RE
{
	class IDLE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kParent = 1 << 0,
			kSequence = 1 << 1,
			kNoAttacking = 1 << 2,
			kBlocking = 1 << 3
		};

		// members
		std::uint8_t loopMin;					 // 00
		std::uint8_t loopMax;					 // 01
		REX::EnumSet<Flags, std::uint8_t> flags; // 02
		std::uint16_t replayDelay;				 // 04
	};
	static_assert(sizeof(IDLE_DATA) == 0x06);
}

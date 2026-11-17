#pragma once

namespace RE
{
	class IDLE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			Parent = 1 << 0,
			Sequence = 1 << 1,
			NoAttacking = 1 << 2,
			Blocking = 1 << 3
		};

		// members
		std::uint8_t loopMin;					 // 0x00
		std::uint8_t loopMax;					 // 0x01
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x02
		std::uint16_t replayDelay;				 // 0x04
	};

	static_assert(sizeof(IDLE_DATA) == 0x06);
}

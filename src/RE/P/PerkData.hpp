#pragma once

namespace RE
{
	class PerkData
	{
	public:
		// members
		bool trait;			   // 0x00
		std::uint8_t level;	   // 0x01
		std::uint8_t numRanks; // 0x02
		bool playable;		   // 0x03
		bool hidden;		   // 0x04
	};

	static_assert(sizeof(PerkData) == 0x05);
}

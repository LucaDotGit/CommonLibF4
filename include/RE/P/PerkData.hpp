#pragma once

namespace RE
{
	class PerkData
	{
	public:
		// members
		bool trait;			   // 00
		std::uint8_t level;	   // 01
		std::uint8_t numRanks; // 02
		bool playable;		   // 03
		bool hidden;		   // 04
	};
	static_assert(sizeof(PerkData) == 0x05);
}

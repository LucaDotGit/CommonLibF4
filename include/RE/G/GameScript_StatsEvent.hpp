#pragma once

namespace RE
{
	class StatsEvent
	{
	public:
		// members
		std::uint32_t timerCount;		  // 00
		std::uint32_t losEventCount;	  // 04
		std::uint32_t distanceEventCount; // 08
		std::uint32_t persistCount;		  // 0C
		std::uint32_t pageMemSize;		  // 10
	};
	static_assert(sizeof(StatsEvent) == 0x14);
}

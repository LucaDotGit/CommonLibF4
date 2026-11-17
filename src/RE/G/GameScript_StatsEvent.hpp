#pragma once

namespace RE
{
	class StatsEvent
	{
	public:
		// members
		std::uint32_t timerCount;		  // 0x00
		std::uint32_t losEventCount;	  // 0x04
		std::uint32_t distanceEventCount; // 0x08
		std::uint32_t persistCount;		  // 0x0C
		std::uint32_t pageMemSize;		  // 0x10
	};

	static_assert(sizeof(StatsEvent) == 0x14);
}

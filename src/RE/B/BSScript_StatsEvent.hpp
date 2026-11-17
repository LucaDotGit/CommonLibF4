#pragma once

namespace RE::BSScript
{
	class StatsEvent
	{
	public:
		// members
		std::uint32_t runningStacksCount;	// 0x00
		std::uint32_t suspendedStacksCount; // 0x04
		std::uint32_t functionMsgCount;		// 0x08
		std::uint32_t detachedObjectCount;	// 0x0C
	};

	static_assert(sizeof(StatsEvent) == 0x10);
}

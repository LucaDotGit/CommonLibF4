#pragma once

namespace RE
{
	class hkStopwatch
	{
	public:
		// members
		std::int64_t ticksAtStart; // 0x00
		std::int64_t ticksTotal;   // 0x08
		std::int64_t ticksAtSplit; // 0x10
		std::int64_t splitTotal;   // 0x18
		bool runningFlag;		   // 0x20
		std::int32_t numTimings;   // 0x24
		const char* name;		   // 0x28
	};

	static_assert(sizeof(hkStopwatch) == 0x30);
}

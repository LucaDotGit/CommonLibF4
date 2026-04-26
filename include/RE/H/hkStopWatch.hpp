#pragma once

namespace RE
{
	class hkStopWatch
	{
	public:
		// members
		std::int64_t ticksAtStart; // 00
		std::int64_t ticksTotal;   // 08
		std::int64_t ticksAtSplit; // 10
		std::int64_t splitTotal;   // 18
		bool runningFlag;		   // 20
		std::int32_t numTimings;   // 24
		const char* name;		   // 28
	};
	static_assert(sizeof(hkStopWatch) == 0x30);
}

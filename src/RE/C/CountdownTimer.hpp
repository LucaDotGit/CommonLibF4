#pragma once

namespace RE
{
	class CountdownTimer
	{
	public:
		// members
		std::uint64_t startTime; // 0x00
		std::uint64_t endTime;	 // 0x08
		bool active;			 // 0x10
	};

	static_assert(sizeof(CountdownTimer) == 0x18);
}

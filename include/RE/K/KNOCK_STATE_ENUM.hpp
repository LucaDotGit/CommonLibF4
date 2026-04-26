#pragma once

namespace RE
{
	enum class KNOCK_STATE_ENUM : std::uint32_t
	{
		kNormal = 0,
		kExplode = 1,
		kExplodeLeadIn = 2,
		kOut = 3,
		kOutLeadIn = 4,
		kQueued = 5,
		kGetUp = 6,
		kDown = 7,
		kWaitForTaskQueue = 8
	};
}

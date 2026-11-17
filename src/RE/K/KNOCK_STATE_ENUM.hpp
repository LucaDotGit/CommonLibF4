#pragma once

namespace RE
{
	enum class KNOCK_STATE_ENUM : std::uint32_t
	{
		Normal = 0,
		Explode = 1,
		ExplodeLeadIn = 2,
		Out = 3,
		OutLeadIn = 4,
		Queued = 5,
		GetUp = 6,
		Down = 7,
		WaitForTaskQueue = 8
	};
}

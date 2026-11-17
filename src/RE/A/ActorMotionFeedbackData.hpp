#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class ActorMotionFeedbackData
	{
	public:
		// members
		NiPoint3 desiredWorldDelta;		// 0x00
		NiPoint3 actualWorldDelta;		// 0x0C
		REX::Float32 previousSpeed;		// 0x18
		REX::Float32 previousDirection; // 0x1C
		REX::Float32 currentHeading;	// 0x20
	};

	static_assert(sizeof(ActorMotionFeedbackData) == 0x24);
}

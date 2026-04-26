#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class ActorMotionFeedbackData
	{
	public:
		// members
		NiPoint3 desiredWorldDelta;		// 00
		NiPoint3 actualWorldDelta;		// 0C
		REX::Float32 previousSpeed;		// 18
		REX::Float32 previousDirection; // 1C
		REX::Float32 currentHeading;	// 20
	};
	static_assert(sizeof(ActorMotionFeedbackData) == 0x24);
}

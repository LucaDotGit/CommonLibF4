#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSActorEvent
	{
	public:
		// member
		ActorHandle actor; // 0x00
	};

	static_assert(sizeof(BGSActorEvent) == 0x04);
}

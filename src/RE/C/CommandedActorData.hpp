#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class CommandedActorData
	{
	public:
		// members
		ActorHandle commandedActor; // 0x00
		ActiveEffect* activeEffect; // 0x08
	};

	static_assert(sizeof(CommandedActorData) == 0x10);
}

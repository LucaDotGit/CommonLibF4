#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PlayerAutoAimActorEvent
		: public BSTValueEvent<ActorHandle> // 00
	{
	public:
	};
	static_assert(sizeof(PlayerAutoAimActorEvent) == 0x08);
}

#pragma once

#include "RE/B/BGSActorEvent.hpp"

namespace RE
{
	class BGSActorDeathEvent
		: public BGSActorEvent // 00
	{
	public:
		// members
		ActorHandle attackerActor; // 04
		REX::Float32 damage;	   // 08
	};
	static_assert(sizeof(BGSActorDeathEvent) == 0x0C);
}

#pragma once

#include "RE/B/BGSActorEvent.hpp"

namespace RE
{
	class BGSActorDeathEvent : public BGSActorEvent // 0x00
	{
	public:
		// members
		ActorHandle attackerActor; // 0x04
		REX::Float32 damage;	   // 0x08
	};

	static_assert(sizeof(BGSActorDeathEvent) == 0x0C);
}

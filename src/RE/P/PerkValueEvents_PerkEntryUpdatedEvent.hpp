#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class BGSPerkEntry;
}

namespace RE::PerkValueEvents
{
	class PerkEntryUpdatedEvent
	{
	public:
		// members
		ActorHandle ownerActor;	 // 0x00
		BGSPerkEntry* perkEntry; // 0x08
	};

	static_assert(sizeof(PerkEntryUpdatedEvent) == 0x10);
}

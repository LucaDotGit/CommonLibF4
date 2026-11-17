#pragma once

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent
	{
	public:
		// members
		ActorValueInfo* actorValue; // 0x00
		TESObjectREFR* ownerRef;	// 0x08
	};

	static_assert(sizeof(ActorValueChangedEvent) == 0x10);
}

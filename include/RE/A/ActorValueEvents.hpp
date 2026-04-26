#pragma once

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent
	{
	public:
		// members
		ActorValueInfo* actorValue; // 00
		TESObjectREFR* ownerRef;	// 08
	};
	static_assert(sizeof(ActorValueChangedEvent) == 0x10);
}

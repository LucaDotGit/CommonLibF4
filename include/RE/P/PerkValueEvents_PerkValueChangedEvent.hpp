#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE::PerkValueEvents
{
	enum class EventType : std::int32_t;

	class PerkValueChangedEvent
	{
	public:
		// members
		REX::Enum<EventType, std::int32_t> changeType; // 00
		ActorHandle ownerActor;						   // 04
		BGSPerk* perk;								   // 08
		std::uint8_t rank;							   // 10
	};
	static_assert(sizeof(PerkValueChangedEvent) == 0x18);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE::PerkValueEvents
{
	enum class EventType : std::int32_t;

	class PerkValueChangedEvent
	{
	public:
		// members
		REX::Enum<EventType, std::int32_t> changeType; // 0x00
		ActorHandle ownerActor;						   // 0x04
		BGSPerk* perk;								   // 0x08
		std::uint8_t rank;							   // 0x10
	};

	static_assert(sizeof(PerkValueChangedEvent) == 0x18);
}

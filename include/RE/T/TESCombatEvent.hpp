#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class ACTOR_COMBAT_STATE : std::int32_t;

	class TESCombatEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESCombatEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESCombatEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESCombatEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sourceActorRef;			  // 00
		NiPointer<TESObjectREFR> targetActorRef;			  // 08
		REX::Enum<ACTOR_COMBAT_STATE, std::int32_t> newState; // 10
	};
	static_assert(sizeof(TESCombatEvent) == 0x18);
}

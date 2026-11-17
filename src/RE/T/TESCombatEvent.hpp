#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class ACTOR_COMBAT_STATE : std::int32_t;

	class TESCombatEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESCombatEvent>*
		{
			using FuncType = decltype(&TESCombatEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCombatEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sourceActorRef;			  // 0x00
		NiPointer<TESObjectREFR> targetActorRef;			  // 0x08
		REX::Enum<ACTOR_COMBAT_STATE, std::int32_t> newState; // 0x10
	};

	static_assert(sizeof(TESCombatEvent) == 0x18);
}

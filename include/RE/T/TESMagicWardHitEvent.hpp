#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESMagicWardHitEvent
	{
	public:
		enum class Status : std::int32_t; // TODO

		[[nodiscard]] static BSTEventSource<TESMagicWardHitEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESMagicWardHitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESMagicWardHitEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef;		// 00
		NiPointer<TESObjectREFR> casterRef;		// 08
		TESFormID spellFormID;					// 10
		REX::Enum<Status, std::int32_t> status; // 14
	};
	static_assert(sizeof(TESMagicWardHitEvent) == 0x18);
}

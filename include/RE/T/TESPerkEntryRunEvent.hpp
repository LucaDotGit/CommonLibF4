#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESPerkEntryRunEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESPerkEntryRunEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESPerkEntryRunEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESPerkEntryRunEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef;	   // 00
		NiPointer<TESObjectREFR> perkOwnerRef; // 08
		TESFormID perkFormID;				   // 10
		std::uint16_t perkEntryID;			   // 14
	};
	static_assert(sizeof(TESPerkEntryRunEvent) == 0x18);
}

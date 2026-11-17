#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESPerkEntryRunEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESPerkEntryRunEvent>*
		{
			using FuncType = decltype(&TESPerkEntryRunEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESPerkEntryRunEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef;	   // 0x00
		NiPointer<TESObjectREFR> perkOwnerRef; // 0x08
		TESFormID perkFormID;				   // 0x10
		std::uint16_t perkEntryID;			   // 0x14
	};

	static_assert(sizeof(TESPerkEntryRunEvent) == 0x18);
}

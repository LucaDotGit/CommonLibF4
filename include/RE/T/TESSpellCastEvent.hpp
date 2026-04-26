#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSpellCastEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESSpellCastEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESSpellCastEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESSpellCastEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> casterRef; // 00
		TESFormID spellFormID;				// 08
	};
	static_assert(sizeof(TESSpellCastEvent) == 0x10);
}

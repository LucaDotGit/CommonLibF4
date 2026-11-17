#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESSpellCastEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSpellCastEvent>*
		{
			using FuncType = decltype(&TESSpellCastEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSpellCastEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> casterRef; // 0x00
		TESFormID spellFormID;				// 0x08
	};

	static_assert(sizeof(TESSpellCastEvent) == 0x10);
}

#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESMagicEffectApplyEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESMagicEffectApplyEvent>*
		{
			using FuncType = decltype(&TESMagicEffectApplyEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESMagicEffectApplyEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 0x00
		NiPointer<TESObjectREFR> casterRef; // 0x08
		TESFormID magicEffectFormID;		// 0x10
	};

	static_assert(sizeof(TESMagicEffectApplyEvent) == 0x18);
}

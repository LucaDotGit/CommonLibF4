#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESMagicEffectApplyEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESMagicEffectApplyEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESMagicEffectApplyEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESMagicEffectApplyEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 00
		NiPointer<TESObjectREFR> casterRef; // 08
		TESFormID magicEffectFormID;		// 10
	};
	static_assert(sizeof(TESMagicEffectApplyEvent) == 0x18);
}

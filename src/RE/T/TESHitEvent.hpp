#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/H/HitData.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESHitEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESHitEvent>*
		{
			using FuncType = decltype(&TESHitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESHitEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		HitData hitData;					// 0x000
		NiPointer<TESObjectREFR> targetRef; // 0x0E0
		NiPointer<TESObjectREFR> causeRef;	// 0x0E8
		BSFixedString material;				// 0x0F0
		TESFormID sourceFormID;				// 0x0F8
		TESFormID projectileFormID;			// 0x0FC
		bool usesHitData;					// 0x100
	};

	static_assert(sizeof(TESHitEvent) == 0x110);
}

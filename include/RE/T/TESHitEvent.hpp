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
		[[nodiscard]] static BSTEventSource<TESHitEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESHitEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESHitEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		HitData hitData;					// 000
		NiPointer<TESObjectREFR> targetRef; // 0E0
		NiPointer<TESObjectREFR> causeRef;	// 0E8
		BSFixedString material;				// 0F0
		TESFormID sourceFormID;				// 0F8
		TESFormID projectileFormID;			// 0FC
		bool usesHitData;					// 100
	};
	static_assert(sizeof(TESHitEvent) == 0x110);
}

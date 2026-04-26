#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESLimbCrippleEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESLimbCrippleEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESLimbCrippleEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESLimbCrippleEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 00
		ActorValueInfo* limbInfo;			// 08
		bool crippled;						// 10
		bool partial;						// 11
	};
	static_assert(sizeof(TESLimbCrippleEvent) == 0x18);
}

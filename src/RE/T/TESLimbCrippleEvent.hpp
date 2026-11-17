#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESLimbCrippleEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESLimbCrippleEvent>*
		{
			using FuncType = decltype(&TESLimbCrippleEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESLimbCrippleEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 0x00
		ActorValueInfo* limbInfo;			// 0x08
		bool crippled;						// 0x10
		bool partial;						// 0x11
	};

	static_assert(sizeof(TESLimbCrippleEvent) == 0x18);
}

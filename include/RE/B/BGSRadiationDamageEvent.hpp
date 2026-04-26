#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSRadiationDamageEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSRadiationDamageEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSRadiationDamageEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSRadiationDamageEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
		bool ingested;				  // 08
	};
	static_assert(sizeof(BGSRadiationDamageEvent) == 0x10);
}

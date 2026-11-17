#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSRadiationDamageEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSRadiationDamageEvent>*
		{
			using FuncType = decltype(&BGSRadiationDamageEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSRadiationDamageEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 0x00
		bool ingested;				  // 0x08
	};

	static_assert(sizeof(BGSRadiationDamageEvent) == 0x10);
}

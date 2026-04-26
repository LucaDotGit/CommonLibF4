#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESActiveEffectApplyRemoveEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESActiveEffectApplyRemoveEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESActiveEffectApplyRemoveEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESActiveEffectApplyRemoveEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> casterRef; // 00
		NiPointer<TESObjectREFR> targetRef; // 08
		ContainerID activeEffectUniqueID;	// 10
		bool applied;						// 12
	};
	static_assert(sizeof(TESActiveEffectApplyRemoveEvent) == 0x18);
}

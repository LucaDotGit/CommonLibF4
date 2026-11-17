#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESActiveEffectApplyRemoveEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESActiveEffectApplyRemoveEvent>*
		{
			using FuncType = decltype(&TESActiveEffectApplyRemoveEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESActiveEffectApplyRemoveEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> casterRef; // 0x00
		NiPointer<TESObjectREFR> targetRef; // 0x08
		ContainerID activeEffectUniqueID;	// 0x10
		bool applied;						// 0x12
	};

	static_assert(sizeof(TESActiveEffectApplyRemoveEvent) == 0x18);
}

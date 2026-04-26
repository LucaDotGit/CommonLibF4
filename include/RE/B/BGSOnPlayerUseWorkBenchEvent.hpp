#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerUseWorkBenchEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerUseWorkBenchEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerUseWorkbenchEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workbenchRef; // 00
	};
	static_assert(sizeof(BGSOnPlayerUseWorkBenchEvent) == 0x08);
}

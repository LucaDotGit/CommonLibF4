#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerCompanionDismiss
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerCompanionDismiss>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerCompanionDismiss::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerCompanionDismiss::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
	};
	static_assert(sizeof(BGSOnPlayerCompanionDismiss) == 0x08);
}

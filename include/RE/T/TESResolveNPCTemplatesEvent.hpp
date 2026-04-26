#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESResolveNPCTemplatesEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESResolveNPCTemplatesEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESResolveNPCTemplatesEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESResolveNPCTemplatesEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID npcFormID; // 00
	};
	static_assert(sizeof(TESResolveNPCTemplatesEvent) == 0x04);
}

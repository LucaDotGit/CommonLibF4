#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESCellFullyLoadedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESCellFullyLoadedEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESCellFullyLoadedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESCellFullyLoadedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESObjectCELL* cell; // 00
	};
	static_assert(sizeof(TESCellFullyLoadedEvent) == 0x08);
}

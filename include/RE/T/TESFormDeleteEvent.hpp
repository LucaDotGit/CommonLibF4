#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESFormDeleteEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESFormDeleteEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESFormDeleteEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFormDeleteEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID formID; // 00
	};
	static_assert(sizeof(TESFormDeleteEvent) == 0x04);
}

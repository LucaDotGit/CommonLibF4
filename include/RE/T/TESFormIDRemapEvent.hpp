#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESFormIDRemapEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESFormIDRemapEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESFormIDRemapEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESFormIDRemapEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID oldFormID; // 00
		TESFormID newFormID; // 04
	};
	static_assert(sizeof(TESFormIDRemapEvent) == 0x08);
}

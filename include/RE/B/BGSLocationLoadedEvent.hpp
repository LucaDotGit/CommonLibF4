#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSLocationLoadedEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSLocationLoadedEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSLocationLoadedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSLocationLoadedEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		BGSLocation* location; // 00
	};
	static_assert(sizeof(BGSLocationLoadedEvent) == 0x08);
}

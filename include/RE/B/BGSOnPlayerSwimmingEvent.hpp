#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSOnPlayerSwimmingEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerSwimmingEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerSwimmingEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerSwimmingEvent::GetEventSource };
			return std::invoke(FUNC);
		}
	};
	static_assert(std::is_empty_v<BGSOnPlayerSwimmingEvent>);
}

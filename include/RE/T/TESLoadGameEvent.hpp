#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESLoadGameEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESLoadGameEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESLoadGameEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESLoadGameEvent::GetEventSource };
			return std::invoke(FUNC);
		}
	};
	static_assert(std::is_empty_v<TESLoadGameEvent>);
}

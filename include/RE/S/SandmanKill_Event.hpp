#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::SandmanKill
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::SandmanKill::Event::GetEventSource };
			return std::invoke(FUNC);
		}
	};
	static_assert(std::is_empty_v<Event>);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::DaysJailed
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::DaysJailed::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		std::int32_t days; // 0x00
	};

	static_assert(sizeof(Event) == 0x04);
}

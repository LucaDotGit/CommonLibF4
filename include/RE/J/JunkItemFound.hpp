#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::JunkItemFound
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<JunkItemFound::Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::JunkItemFound::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		std::uint32_t amount; // 00
	};
	static_assert(sizeof(Event) == 0x04);
}

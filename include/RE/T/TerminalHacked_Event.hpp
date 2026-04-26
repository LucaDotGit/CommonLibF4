#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE::TerminalHacked
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TerminalHacked::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle terminalRef; // 00
	};
	static_assert(sizeof(Event) == 0x04);
}

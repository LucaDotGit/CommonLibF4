#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE::TerminalHacked
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TerminalHacked::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle terminalRef; // 0x00
	};

	static_assert(sizeof(Event) == 0x04);
}

#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE::ChestLooted
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ChestLooted::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandle chestRef; // 0x00
	};

	static_assert(sizeof(Event) == 0x04);
}

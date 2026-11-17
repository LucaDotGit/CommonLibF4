#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::PlayerInDialogueChanged
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PlayerInDialogueChanged::Event::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		bool isPlayerInDialogue; // 0x00
	};

	static_assert(sizeof(Event) == 0x01);
}

#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSEventProcessedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSEventProcessedEvent>*
		{
			using FuncType = decltype(&BGSEventProcessedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSEventProcessedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		std::uint32_t eventID; // 0x00
		bool startedQuest;	   // 0x04
	};

	static_assert(sizeof(BGSEventProcessedEvent) == 0x08);
}

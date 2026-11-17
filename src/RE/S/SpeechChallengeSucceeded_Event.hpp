#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::SpeechChallengeSucceeded
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::SpeechChallengeSucceeded::Event::GetEventSource);
			return std::invoke(FUNC);
		}
	};

	static_assert(std::is_empty_v<Event>);
}

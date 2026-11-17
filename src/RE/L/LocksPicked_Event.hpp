#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::LocksPicked
{
	class Event
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<LocksPicked::Event>*
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::LocksPicked::Event::GetEventSource);
			return std::invoke(FUNC);
		}
	};

	static_assert(std::is_empty_v<LocksPicked::Event>);
}

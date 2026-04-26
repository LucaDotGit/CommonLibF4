#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class ACTOR_LIFE_STATE : std::uint32_t;
}

namespace RE::PlayerLifeStateChanged
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerLifeStateChanged::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<ACTOR_LIFE_STATE, std::uint32_t> lifeState; // 00
	};
	static_assert(sizeof(Event) == 0x04);
}

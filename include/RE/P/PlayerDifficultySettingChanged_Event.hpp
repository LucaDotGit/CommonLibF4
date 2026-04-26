#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	enum class DifficultyLevel : std::int32_t;
}

namespace RE::PlayerDifficultySettingChanged
{
	class Event
	{
	public:
		[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
		{
			using FuncType = decltype(&Event::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PlayerDifficultySettingChanged::Event::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<DifficultyLevel, std::int32_t> oldDifficulty; // 00
		REX::Enum<DifficultyLevel, std::int32_t> newDifficulty; // 04
	};
	static_assert(sizeof(Event) == 0x08);
}

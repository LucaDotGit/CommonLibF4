#pragma once

namespace RE
{
	class BGSIncreaseLevelEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSIncreaseLevelEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		std::uint32_t newLevel; // 00
	};
	static_assert(sizeof(BGSIncreaseLevelEvent) == 0x04);
}

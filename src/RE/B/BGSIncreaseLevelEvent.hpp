#pragma once

namespace RE
{
	class BGSIncreaseLevelEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSIncreaseLevelEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		std::uint32_t newLevel; // 0x00
	};

	static_assert(sizeof(BGSIncreaseLevelEvent) == 0x04);
}

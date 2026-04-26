#pragma once

namespace RE
{
	class BGSLocationLoadedStoryEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSLocationLoadedStoryEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location; // 00
	};
	static_assert(sizeof(BGSLocationLoadedStoryEvent) == 0x08);
}

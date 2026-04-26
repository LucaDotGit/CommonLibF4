#pragma once

namespace RE
{
	class BGSClearLocationEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSClearLocationEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		BGSLocation* location; // 00
	};
	static_assert(sizeof(BGSClearLocationEvent) == 0x08);
}

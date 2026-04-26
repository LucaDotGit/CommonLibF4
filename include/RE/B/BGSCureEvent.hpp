#pragma once

namespace RE
{
	class BGSCureEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSCureEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		TESForm* infection; // 00
	};
	static_assert(sizeof(BGSCureEvent) == 0x08);
}

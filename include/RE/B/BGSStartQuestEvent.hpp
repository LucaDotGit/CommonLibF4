#pragma once

namespace RE
{
	class BGSStartQuestEvent
	{
	public:
		[[nodiscard]] static std::uint32_t& GetEventIndex()
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>{ ID::BGSStartQuestEvent::EventIndex };
			return *EVENT_INDEX;
		}

		// members
		TESQuest* quest; // 00
	};
	static_assert(sizeof(BGSStartQuestEvent) == 0x08);
}

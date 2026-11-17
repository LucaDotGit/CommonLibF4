#pragma once

namespace RE
{
	class BGSStartQuestEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventIndex() noexcept -> std::uint32_t&
		{
			static const auto EVENT_INDEX = REL::Relocation<std::uint32_t*>(ID::BGSStartQuestEvent::EventIndex);
			return *EVENT_INDEX;
		}

		// members
		TESQuest* quest; // 0x00
	};

	static_assert(sizeof(BGSStartQuestEvent) == 0x08);
}

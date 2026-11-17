#pragma once

namespace RE::TESQuestEvent
{
	class Event
	{
	public:
		enum class EventType : std::int32_t
		{
			UpdateQuestActiveStatus = 0,
			UpdateQuestEnableStatus = 1,
			UpdateQuestStageChange = 2,
			UpdateMiscQuestVisibility = 3
		};

		// members
		REX::Enum<EventType, std::int32_t> eventType; // 0x00
		TESQuest* quest;							  // 0x08
	};

	static_assert(sizeof(Event) == 0x10);
}

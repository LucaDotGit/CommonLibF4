#pragma once

namespace RE::TESQuestEvent
{
	class Event
	{
	public:
		enum class EventType : std::int32_t
		{
			kUpdateQuestActiveStatus = 0,
			kUpdateQuestEnableStatus = 1,
			kUpdateQuestStageChange = 2,
			kUpdateMiscQuestVisibility = 3
		};

		// members
		REX::Enum<EventType, std::int32_t> eventType; // 00
		TESQuest* quest;							  // 08
	};
	static_assert(sizeof(Event) == 0x10);
}

#pragma once

#include "RE/B/BGSLocalizedStringDL.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESCondition.hpp"

namespace RE
{
	class TESQuestStage;

	class TESQuestStageItem
	{
	public:
		GAME_HEAP_REDEFINE_NEW(TESQuestStageItem);

		// members
		TESCondition conditions;	   // 00
		TESQuest* nextQuest;		   // 08
		BGSLocalizedStringDL logEntry; // 10
		std::uint8_t data;			   // 14
		std::uint8_t index;			   // 15
		bool hasLogEntry;			   // 16
		TESQuest* ownerQuest;		   // 18
		TESQuestStage* owningStage;	   // 20
	};
	static_assert(sizeof(TESQuestStageItem) == 0x28);
}

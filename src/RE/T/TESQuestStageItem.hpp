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
		TESCondition conditions;	   // 0x00
		TESQuest* nextQuest;		   // 0x08
		BGSLocalizedStringDL logEntry; // 0x10
		std::uint8_t data;			   // 0x14
		std::uint8_t index;			   // 0x15
		bool hasLogEntry;			   // 0x16
		TESQuest* ownerQuest;		   // 0x18
		TESQuestStage* owningStage;	   // 0x20
	};

	static_assert(sizeof(TESQuestStageItem) == 0x28);
}

#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/Q/QUEST_STAGE_DATA.hpp"

namespace RE
{
	class TESQuestStageItem;

	class TESQuestStage
	{
	public:
		GAME_HEAP_REDEFINE_NEW(TESQuestStage);

		// members
		BSTArray<TESQuestStageItem*> stageItems; // 00
		QUEST_STAGE_DATA data;					 // 18
	};
	static_assert(sizeof(TESQuestStage) == 0x20);
}

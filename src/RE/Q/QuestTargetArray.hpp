#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class TESQuestTarget;

	class QuestTargetArray : public BSTArray<TESQuestTarget*> // 0x00
	{
	public:
		// members
		std::uint64_t nextRepath; // 0x18
	};

	static_assert(sizeof(QuestTargetArray) == 0x20);
}

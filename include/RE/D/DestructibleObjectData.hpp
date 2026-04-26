#pragma once

#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class DestructibleObjectStage;
	class QueuedFile;

	class DestructibleObjectData
	{
	public:
		GAME_HEAP_REDEFINE_NEW(DestructibleObjectData);

		// members
		std::uint32_t health;														// 00
		std::int8_t numStages;														// 04
		std::int8_t flags;															// 05
		SimpleArray<DestructibleObjectStage*> stagesArray;							// 08
		BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 10
		volatile std::int32_t replacementModelRefCount;								// 18
		NiPointer<QueuedFile> preloadedReplacementModels;							// 20
	};
	static_assert(sizeof(DestructibleObjectData) == 0x28);
}

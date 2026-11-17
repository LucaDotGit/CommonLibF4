#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class QueuedPromoteLargeReferencesTask;

	class BGSLargeRefData
	{
	public:
		class REF_CELL_DATA
		{
		public:
			// members
			TESFormID refID;			 // 0x00
			std::uint32_t parentCellKey; // 0x04
		};

		static_assert(sizeof(REF_CELL_DATA) == 0x08);

		// members
		BSTHashMap<TESFormID, BSTArray<REF_CELL_DATA>*> cellOverlappingRefMap;				   // 0x00
		BSTHashMap<TESFormID, NiPointer<QueuedPromoteLargeReferencesTask>> cellPromoteTaskMap; // 0x30
	};

	static_assert(sizeof(BGSLargeRefData) == 0x60);
}

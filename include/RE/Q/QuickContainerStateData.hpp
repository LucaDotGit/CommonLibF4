#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/I/InventoryItemDisplayData.hpp"

namespace RE
{
	enum class QuickContainerMode : std::int32_t;

	class QuickContainerStateData
	{
	public:
		// members
		BSTSmallArray<InventoryItemDisplayData, 5> itemDataArray;  // 00
		ObjectRefHandle containerRef;							   // 88
		ObjectRefHandle inventoryRef;							   // 8C
		BSFixedStringCS buttonText;								   // 90
		BSFixedString containerName;							   // 98
		BSFixedStringCS perkButtonText;							   // A0
		std::int32_t selectedClipIndex;							   // A8
		REX::Enum<QuickContainerMode, std::int32_t> containerMode; // AC
		bool perkButtonEnabled;									   // B0
		bool isNewContainer;									   // B1
		bool addedDroppedItems;									   // B2
		bool isLocked;											   // B3
		bool buttonAEnabled;									   // B4
		bool buttonXEnabled;									   // B5
		bool refreshContainerSize;								   // B6
		bool containerActivated;								   // B7
	};
	static_assert(sizeof(QuickContainerStateData) == 0xB8);
}

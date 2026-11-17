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
		BSTSmallArray<InventoryItemDisplayData, 5> itemDataArray;  // 0x00
		ObjectRefHandle containerRef;							   // 0x88
		ObjectRefHandle inventoryRef;							   // 0x8C
		BSFixedStringCS buttonText;								   // 0x90
		BSFixedString containerName;							   // 0x98
		BSFixedStringCS perkButtonText;							   // 0xA0
		std::int32_t selectedClipIndex;							   // 0xA8
		REX::Enum<QuickContainerMode, std::int32_t> containerMode; // 0xAC
		bool perkButtonEnabled;									   // 0xB0
		bool isNewContainer;									   // 0xB1
		bool addedDroppedItems;									   // 0xB2
		bool isLocked;											   // 0xB3
		bool buttonAEnabled;									   // 0xB4
		bool buttonXEnabled;									   // 0xB5
		bool refreshContainerSize;								   // 0xB6
		bool containerActivated;								   // 0xB7
	};

	static_assert(sizeof(QuickContainerStateData) == 0xB8);
}

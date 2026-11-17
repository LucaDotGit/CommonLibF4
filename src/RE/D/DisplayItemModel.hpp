#pragma once

#include "RE/B/BaseLoadedInventoryModel.hpp"

namespace RE
{
	class DisplayItemModel : public BaseLoadedInventoryModel // 0x00
	{
	public:
		// members
		REX::Float32 itemRotation; // 0x40
		std::uint32_t uniqueIndex; // 0x44
		std::uint16_t column;	   // 0x48
		std::uint16_t index;	   // 0x4A
		std::uint16_t row;		   // 0x4C
	};

	static_assert(sizeof(DisplayItemModel) == 0x50);
}

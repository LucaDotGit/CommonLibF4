#pragma once

#include "RE/F/FACTION_VENDOR_DATA_VALUES.hpp"

namespace RE
{
	class PackageLocation;
	class TESCondition;

	class FACTION_VENDOR_DATA
	{
	public:
		// members
		FACTION_VENDOR_DATA_VALUES vendorValues; // 0x00
		PackageLocation* vendorLocation;		 // 0x10
		TESCondition* vendorConditions;			 // 0x18
		BGSListForm* vendorSellBuyList;			 // 0x20
		TESObjectREFR* merchantContainer;		 // 0x28
		std::uint32_t lastDayReset;				 // 0x30
	};

	static_assert(sizeof(FACTION_VENDOR_DATA) == 0x38);
}

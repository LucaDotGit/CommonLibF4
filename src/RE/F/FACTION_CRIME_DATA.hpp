#pragma once

#include "RE/F/FACTION_CRIME_DATA_VALUES.hpp"

namespace RE
{
	class FACTION_CRIME_DATA
	{
	public:
		// members
		TESObjectREFR* factionJailMarker;				// 0x00
		TESObjectREFR* factionWaitMarker;				// 0x08
		TESObjectREFR* factionStolenContainer;			// 0x10
		TESObjectREFR* factionPlayerInventoryContainer; // 0x18
		BGSListForm* crimeGroup;						// 0x20
		BGSOutfit* jailOutfit;							// 0x28
		FACTION_CRIME_DATA_VALUES crimeValues;			// 0x30
	};

	static_assert(sizeof(FACTION_CRIME_DATA) == 0x48);
}

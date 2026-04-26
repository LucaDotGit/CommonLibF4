#pragma once

namespace RE
{
	class ENCOUNTER_ZONE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kNeverReset = 1 << 0,
			kMatchPCBelowMin = 1 << 1,
			kDisableCombatBoundary = 1 << 2,
			kWorkshopZone = 1 << 3
		};

		// members
		TESForm* zoneOwner;						 // 00
		BGSLocation* location;					 // 08
		std::uint8_t ownerRank;					 // 10
		std::uint8_t minLevel;					 // 11
		REX::EnumSet<Flags, std::uint8_t> flags; // 12
		std::uint8_t maxLevel;					 // 13
	};
	static_assert(sizeof(ENCOUNTER_ZONE_DATA) == 0x18);
}

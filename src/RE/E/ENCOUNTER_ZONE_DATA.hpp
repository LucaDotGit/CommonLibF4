#pragma once

namespace RE
{
	class ENCOUNTER_ZONE_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			NeverReset = 1 << 0,
			MatchPCBelowMin = 1 << 1,
			DisableCombatBoundary = 1 << 2,
			WorkshopZone = 1 << 3
		};

		// members
		TESForm* zoneOwner;						 // 0x00
		BGSLocation* location;					 // 0x08
		std::uint8_t ownerRank;					 // 0x10
		std::uint8_t minLevel;					 // 0x11
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x12
		std::uint8_t maxLevel;					 // 0x13
	};

	static_assert(sizeof(ENCOUNTER_ZONE_DATA) == 0x18);
}

#pragma once

namespace RE
{
	class FACTION_DATA
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kHiddenFromPC = 1 << 0,
			kSpecialCombat = 1 << 1,
			kPlayerIsExpelled = 1 << 2,
			kPlayerIsEnemy = 1 << 3,
			kTrackCrime = 1 << 6,
			kIgnoresCrimes_Murder = 1 << 7,
			kIgnoresCrimes_Assault = 1 << 8,
			kIgnoresCrimes_Stealing = 1 << 9,
			kIgnoresCrimes_Trespass = 1 << 10,
			kDoNotReportCrimesAgainstMembers = 1 << 11,
			kCrimeGold_UseDefaults = 1 << 12,
			kIgnoresCrimes_Pickpocket = 1 << 13,
			kVendor = 1 << 14,
			kCanBeOwner = 1 << 15
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags; // 00
	};
	static_assert(sizeof(FACTION_DATA) == 0x04);
}

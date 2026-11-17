#pragma once

namespace RE
{
	class FACTION_DATA
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			HiddenFromPC = 1 << 0,
			SpecialCombat = 1 << 1,
			PlayerIsExpelled = 1 << 2,
			PlayerIsEnemy = 1 << 3,
			TrackCrime = 1 << 6,
			IgnoresCrimes_Murder = 1 << 7,
			IgnoresCrimes_Assault = 1 << 8,
			IgnoresCrimes_Stealing = 1 << 9,
			IgnoresCrimes_Trespass = 1 << 10,
			DoNotReportCrimesAgainstMembers = 1 << 11,
			CrimeGold_UseDefaults = 1 << 12,
			IgnoresCrimes_Pickpocket = 1 << 13,
			Vendor = 1 << 14,
			CanBeOwner = 1 << 15
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x00
	};

	static_assert(sizeof(FACTION_DATA) == 0x04);
}

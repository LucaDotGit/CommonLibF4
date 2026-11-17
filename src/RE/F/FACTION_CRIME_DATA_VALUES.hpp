#pragma once

namespace RE
{
	class FACTION_CRIME_DATA_VALUES
	{
	public:
		// members
		bool arrest;					   // 0x00
		bool attackOnSight;				   // 0x01
		std::uint16_t murderCrimeGold;	   // 0x02
		std::uint16_t assaultCrimeGold;	   // 0x04
		std::uint16_t trespassCrimeGold;   // 0x06
		std::uint16_t pickpocketCrimeGold; // 0x08
		REX::Float32 stealCrimeGoldMult;   // 0x0C
		std::uint16_t escapeCrimeGold;	   // 0x10
		std::uint16_t unused;			   // 0x12
	};

	static_assert(sizeof(FACTION_CRIME_DATA_VALUES) == 0x14);
}

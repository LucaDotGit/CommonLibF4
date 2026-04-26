#pragma once

namespace RE
{
	class NPC_DATA
	{
	public:
		// members
		std::int16_t autoCalcHealth;	   // 00
		std::int16_t autoCalcActionPoints; // 02
		std::uint16_t farDistance;		   // 04
		std::int8_t gearedUpWeapons;	   // 06
	};
	static_assert(sizeof(NPC_DATA) == 0x08);
}

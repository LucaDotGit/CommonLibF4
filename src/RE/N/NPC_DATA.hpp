#pragma once

namespace RE
{
	class NPC_DATA
	{
	public:
		// members
		std::int16_t autoCalcHealth;	   // 0x00
		std::int16_t autoCalcActionPoints; // 0x02
		std::uint16_t farDistance;		   // 0x04
		std::int8_t gearedUpWeapons;	   // 0x06
	};

	static_assert(sizeof(NPC_DATA) == 0x08);
}

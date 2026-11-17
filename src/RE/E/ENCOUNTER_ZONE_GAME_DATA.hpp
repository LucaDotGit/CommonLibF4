#pragma once

namespace RE
{
	class ENCOUNTER_ZONE_GAME_DATA
	{
	public:
		// members
		std::uint32_t detachTime; // 0x00
		std::uint32_t attachTime; // 0x04
		std::uint32_t resetTime;  // 0x08
		std::uint16_t zoneLevel;  // 0x0C
	};

	static_assert(sizeof(ENCOUNTER_ZONE_GAME_DATA) == 0x10);
}

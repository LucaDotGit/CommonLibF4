#pragma once

namespace RE
{
	class FACTION_RANK
	{
	public:
		// members
		TESFaction* faction; // 0x00
		std::int8_t rank;	 // 0x08
	};

	static_assert(sizeof(FACTION_RANK) == 0x10);
}

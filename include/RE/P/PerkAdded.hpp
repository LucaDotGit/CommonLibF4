#pragma once

namespace RE::PerkAdded
{
	class Event
	{
	public:
		// members
		Actor* actor;		  // 00
		BGSPerk* perk;		  // 08
		std::uint8_t newRank; // 10
	};
	static_assert(sizeof(Event) == 0x18);
}

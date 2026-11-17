#pragma once

namespace RE::PerkAdded
{
	class Event
	{
	public:
		// members
		Actor* actor;		  // 0x00
		BGSPerk* perk;		  // 0x08
		std::uint8_t newRank; // 0x10
	};

	static_assert(sizeof(Event) == 0x18);
}

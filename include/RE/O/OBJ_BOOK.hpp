#pragma once

namespace RE
{
	class OBJ_BOOK
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kAdvancesActorValue = 1 << 0,
			kCannotTake = 1 << 1,
			kAddSpell = 1 << 2,
			kHasBeenRead = 1 << 3,
			kAddPerk = 1 << 4
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 00
		union
		{
			ActorValueInfo* actorValueToAdvance;
			SpellItem* spell;
			BGSPerk* perk;
		} teaches;				   // 08
		std::uint32_t textOffsetX; // 10
		std::uint32_t textOffsetY; // 14
	};
	static_assert(sizeof(OBJ_BOOK) == 0x18);
}

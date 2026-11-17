#pragma once

namespace RE
{
	class OBJ_BOOK
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			AdvancesActorValue = 1 << 0,
			CannotTake = 1 << 1,
			AddSpell = 1 << 2,
			HasBeenRead = 1 << 3,
			AddPerk = 1 << 4
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x00

		union
		{
		public:
			ActorValueInfo* actorValueToAdvance;
			SpellItem* spell;
			BGSPerk* perk;
		} teaches; // 0x08

		std::uint32_t textOffsetX; // 0x10
		std::uint32_t textOffsetY; // 0x14
	};

	static_assert(sizeof(OBJ_BOOK) == 0x18);
}

#pragma once

namespace RE::MagicSystem
{
	enum class CannotCastReason : std::int32_t
	{
		None = 0,
		Magicka = 1,
		PowerUsed = 2,
		RangedUnderWater = 3,
		MultipleCast = 4,
		ItemCharge = 5,
		CastWhileShouting = 6,
		ShoutWhileCasting = 7,
		ShoutWhileRecovering = 8,

		_Count = 9,

		CustomReasonNoStart = 100
	};

	enum class CastingSource : std::int32_t
	{
		None = -1,
		LeftHand = 0,
		RightHand = 1,
		Other = 2,
		Instant = 3,

		_Count = 4
	};

	enum class CastingType : std::int32_t
	{
		None = -1,
		ConstantEffect = 0,
		FireAndForget = 1,
		Concentration = 2,
		Scroll = 3,

		_Count = 4
	};

	enum class Delivery : std::int32_t
	{
		None = -1,
		Self = 0,
		Touch = 1,
		Aimed = 2,
		TargetActor = 3,
		TargetLocation = 4,

		_Count = 5
	};

	enum class SoundID : std::int32_t
	{
		None = -1,
		DrawSheatheLPM = 0,
		Charge = 1,
		ReadyLoop = 2,
		Release = 3,
		CastLoop = 4,
		Hit = 5,

		_Count = 6
	};

	enum class SpellType : std::int32_t
	{
		None = -1,
		Spell = 0,
		Disease = 1,
		Power = 2,
		LesserPower = 3,
		Ability = 4,
		Poison = 5,
		Enchantment = 6,

		Potion = 7,
		Alchemy = Potion,

		WordOfPower = 8,
		Ingredient = WordOfPower,

		LeveledSpell = 9,
		Addiction = 10,
		VoicePower = 11,
		StaffEnchantment = 12,
		Scroll = 13,

		_Count = 14
	};

	enum class WardState : std::int32_t
	{
		None = 0,
		Absorb = 1,
		Break = 2,

		_Count = 3
	};
}

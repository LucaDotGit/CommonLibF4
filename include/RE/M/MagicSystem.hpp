#pragma once

namespace RE::MagicSystem
{
	enum class CannotCastReason : std::int32_t
	{
		kNone = 0,
		kMagicka = 1,
		kPowerUsed = 2,
		kRangedUnderWater = 3,
		kMultipleCast = 4,
		kItemCharge = 5,
		kCastWhileShouting = 6,
		kShoutWhileCasting = 7,
		kShoutWhileRecovering = 8,

		kTotal = 9,

		kCustomReasonNoStart = 100
	};

	enum class CastingSource : std::int32_t
	{
		kNone = -1,
		kLeftHand = 0,
		kRightHand = 1,
		kOther = 2,
		kInstant = 3,

		kTotal = 4
	};

	enum class CastingType : std::int32_t
	{
		kNone = -1,
		kConstantEffect = 0,
		kFireAndForget = 1,
		kConcentration = 2,
		kScroll = 3,

		kTotal = 4
	};

	enum class Delivery : std::int32_t
	{
		kNone = -1,
		kSelf = 0,
		kTouch = 1,
		kAimed = 2,
		kTargetActor = 3,
		kTargetLocation = 4,

		kTotal = 5
	};

	enum class SoundID : std::int32_t
	{
		kNone = -1,
		kDrawSheatheLPM = 0,
		kCharge = 1,
		kReadyLoop = 2,
		kRelease = 3,
		kCastLoop = 4,
		kHit = 5,

		kTotal = 6
	};

	enum class SpellType : std::int32_t
	{
		kNone = -1,
		kSpell = 0,
		kDisease = 1,
		kPower = 2,
		kLesserPower = 3,
		kAbility = 4,
		kPoison = 5,
		kEnchantment = 6,

		kPotion = 7,
		kAlchemy = kPotion,

		kWordOfPower = 8,
		kIngredient = kWordOfPower,

		kLeveledSpell = 9,
		kAddiction = 10,
		kVoicePower = 11,
		kStaffEnchantment = 12,
		kScroll = 13,

		kTotal = 14
	};

	enum class WardState : std::int32_t
	{
		kNone = 0,
		kAbsorb = 1,
		kBreak = 2,

		kTotal = 3
	};
}

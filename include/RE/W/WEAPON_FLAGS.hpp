#pragma once

namespace RE
{
	enum class WEAPON_FLAGS : std::uint32_t
	{
		kNone = 0,
		kPlayerOnly = 1 << 0,
		kNPCsUseAmmo = 1 << 1,
		kNoJamAfterReload = 1 << 2,
		kChargingReload = 1 << 3,
		kMinorCrime = 1 << 4,
		kFixedRange = 1 << 5,
		kNotUsedInNormalCombat = 1 << 6,
		kCritEffectOnDeath = 1 << 8,
		kChargingAttack = 1 << 9,
		kHoldInputToPower = 1 << 11,
		kNonHostile = 1 << 12,
		kBoundWeapon = 1 << 13,
		kIgnoresNormalWeaponResistance = 1 << 14,
		kAutomatic = 1 << 15,
		kRepeatableSingleFire = 1 << 16,
		kCantDrop = 1 << 17,
		kHideBackpack = 1 << 18,
		kEmbeddedWeapon = 1 << 19,
		kNotPlayable = 1 << 20,
		kHasScope = 1 << 21,
		kBoltAction = 1 << 22,
		kSecondaryWeapon = 1 << 23,
		kDisableShells = 1 << 24
	};
}

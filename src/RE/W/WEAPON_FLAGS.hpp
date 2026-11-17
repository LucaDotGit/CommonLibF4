#pragma once

namespace RE
{
	enum class WEAPON_FLAGS : std::uint32_t
	{
		None = 0,
		PlayerOnly = 1 << 0,
		NPCsUseAmmo = 1 << 1,
		NoJamAfterReload = 1 << 2,
		ChargingReload = 1 << 3,
		MinorCrime = 1 << 4,
		FixedRange = 1 << 5,
		NotUsedInNormalCombat = 1 << 6,
		CritEffectOnDeath = 1 << 8,
		ChargingAttack = 1 << 9,
		HoldInputToPower = 1 << 11,
		NonHostile = 1 << 12,
		BoundWeapon = 1 << 13,
		IgnoresNormalWeaponResistance = 1 << 14,
		Automatic = 1 << 15,
		RepeatableSingleFire = 1 << 16,
		CantDrop = 1 << 17,
		HideBackpack = 1 << 18,
		EmbeddedWeapon = 1 << 19,
		NotPlayable = 1 << 20,
		HasScope = 1 << 21,
		BoltAction = 1 << 22,
		SecondaryWeapon = 1 << 23,
		DisableShells = 1 << 24
	};
}

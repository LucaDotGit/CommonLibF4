#pragma once

namespace RE
{
	class AMMO_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kIgnoresNormalWeaponResist = 1 << 0,
			kNonPlayable = 1 << 1,
			kHasCountBased3D = 1 << 2
		};

		// members
		BGSProjectile* projectile;				 // 00
		std::uint32_t health;					 // 08
		REX::EnumSet<Flags, std::uint8_t> flags; // 0C
		REX::Float32 damage;					 // 10
	};
	static_assert(sizeof(AMMO_DATA) == 0x18);
}

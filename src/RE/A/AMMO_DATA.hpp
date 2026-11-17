#pragma once

namespace RE
{
	class AMMO_DATA
	{
	public:
		enum class Flags : std::uint8_t
		{
			None = 0,
			IgnoresNormalWeaponResist = 1 << 0,
			NonPlayable = 1 << 1,
			HasCountBased3D = 1 << 2
		};

		// members
		BGSProjectile* projectile;				 // 0x00
		std::uint32_t health;					 // 0x08
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x0C
		REX::Float32 damage;					 // 0x10
	};

	static_assert(sizeof(AMMO_DATA) == 0x18);
}

#pragma once

namespace RE
{
	class AttackData
	{
	public:
		// members
		REX::Float32 damageMult;	   // 0x00
		REX::Float32 attackChance;	   // 0x04
		SpellItem* attackSpell;		   // 0x08
		std::uint32_t flags;		   // 0x10
		REX::Float32 attackAngle;	   // 0x14
		REX::Float32 strikeAngle;	   // 0x18
		std::int32_t staggerOffset;	   // 0x1C
		BGSKeyword* attackType;		   // 0x20
		REX::Float32 knockdown;		   // 0x28
		REX::Float32 recoveryTime;	   // 0x2C
		REX::Float32 actionPointsMult; // 0x30
	};

	static_assert(sizeof(AttackData) == 0x38);
}

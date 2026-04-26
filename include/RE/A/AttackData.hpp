#pragma once

namespace RE
{
	class AttackData
	{
	public:
		// members
		REX::Float32 damageMult;	   // 00
		REX::Float32 attackChance;	   // 04
		SpellItem* attackSpell;		   // 08
		std::uint32_t flags;		   // 10
		REX::Float32 attackAngle;	   // 14
		REX::Float32 strikeAngle;	   // 18
		std::int32_t staggerOffset;	   // 1C
		BGSKeyword* attackType;		   // 20
		REX::Float32 knockdown;		   // 28
		REX::Float32 recoveryTime;	   // 2C
		REX::Float32 actionPointsMult; // 30
	};
	static_assert(sizeof(AttackData) == 0x38);
}

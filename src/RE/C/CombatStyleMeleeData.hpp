#pragma once

namespace RE
{
	class CombatStyleMeleeData
	{
	public:
		// members
		REX::Float32 attackIncapacitatedMult;	   // 0x00
		REX::Float32 powerAttackIncapacitatedMult; // 0x04
		REX::Float32 powerAttackBlockingMult;	   // 0x08
		REX::Float32 bashMult;					   // 0x0C
		REX::Float32 bashRecoiledMult;			   // 0x10
		REX::Float32 bashAttackMult;			   // 0x14
		REX::Float32 bashPowerAttackMult;		   // 0x18
		REX::Float32 specialAttackMult;			   // 0x1C
		REX::Float32 blockWhenIncapacitatedMult;   // 0x20
		REX::Float32 attackWhenIncapacitatedMult;  // 0x24
	};

	static_assert(sizeof(CombatStyleMeleeData) == 0x28);
}

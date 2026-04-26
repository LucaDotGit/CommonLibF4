#pragma once

namespace RE
{
	class CombatStyleMeleeData
	{
	public:
		// members
		REX::Float32 attackIncapacitatedMult;	   // 00
		REX::Float32 powerAttackIncapacitatedMult; // 04
		REX::Float32 powerAttackBlockingMult;	   // 08
		REX::Float32 bashMult;					   // 0C
		REX::Float32 bashRecoiledMult;			   // 10
		REX::Float32 bashAttackMult;			   // 14
		REX::Float32 bashPowerAttackMult;		   // 18
		REX::Float32 specialAttackMult;			   // 1C
		REX::Float32 blockWhenIncapacitatedMult;   // 20
		REX::Float32 attackWhenIncapacitatedMult;  // 24
	};
	static_assert(sizeof(CombatStyleMeleeData) == 0x28);
}

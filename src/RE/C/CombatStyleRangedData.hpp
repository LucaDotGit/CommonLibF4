#pragma once

namespace RE
{
	class CombatStyleRangedData
	{
	public:
		// members
		REX::Float32 accuracyMult; // 0x00
	};

	static_assert(sizeof(CombatStyleRangedData) == 0x04);
}

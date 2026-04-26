#pragma once

namespace RE
{
	class CombatStyleCoverData
	{
	public:
		// members
		REX::Float32 coverSearchDistanceMult; // 00
	};
	static_assert(sizeof(CombatStyleCoverData) == 0x04);
}

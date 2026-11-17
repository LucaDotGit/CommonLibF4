#pragma once

namespace RE
{
	class CombatStyleCoverData
	{
	public:
		// members
		REX::Float32 coverSearchDistanceMult; // 0x00
	};

	static_assert(sizeof(CombatStyleCoverData) == 0x04);
}

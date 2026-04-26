#pragma once

namespace RE
{
	class CombatRange
	{
	public:
		// members
		REX::Float32 minRange; // 00
		REX::Float32 maxRange; // 04
	};
	static_assert(sizeof(CombatRange) == 0x08);
}

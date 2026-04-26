#pragma once

namespace RE
{
	class DisableHeavyItemsFunc
	{
	public:
		// members
		REX::Float32 playerCurrEncumbrance;	   // 00
		REX::Float32 playerMaxEncumbrance;	   // 04
		REX::Float32 containerCurrEncumbrance; // 08
		REX::Float32 containerMaxEncumbrance;  // 0C
	};
	static_assert(sizeof(DisableHeavyItemsFunc) == 0x10);
}

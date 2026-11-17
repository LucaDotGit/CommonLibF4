#pragma once

namespace RE
{
	class DisableHeavyItemsFunc
	{
	public:
		// members
		REX::Float32 playerCurrEncumbrance;	   // 0x00
		REX::Float32 playerMaxEncumbrance;	   // 0x04
		REX::Float32 containerCurrEncumbrance; // 0x08
		REX::Float32 containerMaxEncumbrance;  // 0x0C
	};

	static_assert(sizeof(DisableHeavyItemsFunc) == 0x10);
}

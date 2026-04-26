#pragma once

namespace RE::TESSoundDefs
{
	class RepeaterData
	{
	public:
		// members
		REX::Float32 minDelay; // 00
		REX::Float32 maxDelay; // 04
		bool stackable;		   // 08
	};
	static_assert(sizeof(RepeaterData) == 0x0C);
}

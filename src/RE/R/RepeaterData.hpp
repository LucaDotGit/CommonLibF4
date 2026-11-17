#pragma once

namespace RE::TESSoundDefs
{
	class RepeaterData
	{
	public:
		// members
		REX::Float32 minDelay; // 0x00
		REX::Float32 maxDelay; // 0x04
		bool stackable;		   // 0x08
	};

	static_assert(sizeof(RepeaterData) == 0x0C);
}

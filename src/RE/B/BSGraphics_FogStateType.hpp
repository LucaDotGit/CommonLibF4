#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint4.hpp"

namespace RE::BSGraphics
{
	class FogStateType
	{
	public:
		// members
		NiPoint4 rangeData;			   // 0x00
		NiColor nearLowColor;		   // 0x10
		REX::Float32 power;			   // 0x1C
		NiColor nearHighColor;		   // 0x20
		REX::Float32 clamp;			   // 0x2C
		NiColor farLowColor;		   // 0x30
		REX::Float32 highDensityScale; // 0x3C
		NiColor farHighColor;		   // 0x40
		REX::Float32 padding;		   // 0x4C
		NiPoint4 highLowRangeData;	   // 0x50
	};

	static_assert(sizeof(FogStateType) == 0x60);
}

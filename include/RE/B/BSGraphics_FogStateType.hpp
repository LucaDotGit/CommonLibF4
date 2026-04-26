#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE::BSGraphics
{
	class FogStateType
	{
	public:
		// members
		NiPoint4 rangeData;			   // 00
		NiColor nearLowColor;		   // 10
		REX::Float32 power;			   // 1C
		NiColor nearHighColor;		   // 20
		REX::Float32 clamp;			   // 2C
		NiColor farLowColor;		   // 30
		REX::Float32 highDensityScale; // 3C
		NiColor farHighColor;		   // 40
		REX::Float32 padding;		   // 4C
		NiPoint4 highLowRangeData;	   // 50
	};
	static_assert(sizeof(FogStateType) == 0x60);
}

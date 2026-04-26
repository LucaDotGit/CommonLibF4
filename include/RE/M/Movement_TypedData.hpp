#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/Movement_MaxSpeeds.hpp"

namespace RE::Movement
{
	class TypeData
	{
	public:
		// members
		BSFixedString typeName;		  // 00
		MaxSpeeds defaultData;		  // 08
		REX::Float32 floatHeight;	  // 78
		REX::Float32 flightAngleGain; // 7C
	};
	static_assert(sizeof(TypeData) == 0x80);
}

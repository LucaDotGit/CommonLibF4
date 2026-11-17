#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/Movement_MaxSpeeds.hpp"

namespace RE::Movement
{
	class TypeData
	{
	public:
		// members
		BSFixedString typeName;		  // 0x00
		MaxSpeeds defaultData;		  // 0x08
		REX::Float32 floatHeight;	  // 0x78
		REX::Float32 flightAngleGain; // 0x7C
	};

	static_assert(sizeof(TypeData) == 0x80);
}

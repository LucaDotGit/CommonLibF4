#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class MovementVector
	{
	public:
		// members
		NiPoint3A eulerAngles;		   // 00
		REX::Float32 speed{ 0.0_f32 }; // 10
	};
	static_assert(sizeof(MovementVector) == 0x20);
}

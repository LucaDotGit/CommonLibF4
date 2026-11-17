#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MovementVector
	{
	public:
		// members
		NiPoint3A eulerAngles;								// 0x00
		REX::Float32 speed{static_cast<REX::Float32>(0.0)}; // 0x10
	};

	static_assert(sizeof(MovementVector) == 0x20);
}

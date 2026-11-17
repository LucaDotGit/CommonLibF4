#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MovementTweenerOutputData
	{
	public:
		// members
		NiPoint3 velocity;		// 0x00
		NiPoint3 rotationSpeed; // 0x0C
	};

	static_assert(sizeof(MovementTweenerOutputData) == 0x18);
}

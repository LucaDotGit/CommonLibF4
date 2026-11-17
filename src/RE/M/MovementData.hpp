#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MovementData
	{
	public:
		// members
		NiPoint3A movementRotation; // 0x00
		NiPoint3A rotationSpeed;	// 0x10
		REX::Float32 movementSpeed; // 0x20
	};

	static_assert(sizeof(MovementData) == 0x30);
}

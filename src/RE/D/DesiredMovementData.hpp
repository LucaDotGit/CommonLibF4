#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class DesiredMovementData
	{
	public:
		// members
		NiPoint3A position;		 // 0x00
		NiPoint3A orientation;	 // 0x10
		NiPoint3A movementSpeed; // 0x20
		NiPoint3A rotationSpeed; // 0x30
	};

	static_assert(sizeof(DesiredMovementData) == 0x40);
}

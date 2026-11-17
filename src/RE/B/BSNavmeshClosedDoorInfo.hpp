#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BSPathingDoor;

	class BSNavmeshClosedDoorInfo
	{
	public:
		// members
		BSTSmartPointer<BSPathingDoor> door; // 0x00
		std::uint16_t iriangleIndex;		 // 0x08
	};

	static_assert(sizeof(BSNavmeshClosedDoorInfo) == 0x10);
}

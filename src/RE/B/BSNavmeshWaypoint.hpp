#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSNavmeshWaypoint
	{
	public:
		// members
		NiPoint3 position;			 // 0x00
		std::uint16_t triangleIndex; // 0x0C
		std::uint32_t flags;		 // 0x10
	};

	static_assert(sizeof(BSNavmeshWaypoint) == 0x14);
}

#pragma once

#include "RE/B/BSNavmeshTriHandle.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSNavmeshTriLocation
		: public BSNavmeshTriHandle // 00
	{
		// members
		NiPoint3 location; // 10
	};
	static_assert(sizeof(BSNavmeshTriLocation) == 0x20);
}

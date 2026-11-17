#pragma once

#include "RE/B/BSNavmeshTriHandle.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSNavmeshTriLocation : public BSNavmeshTriHandle // 0x00
	{
		// members
		NiPoint3 location; // 0x10
	};

	static_assert(sizeof(BSNavmeshTriLocation) == 0x20);
}

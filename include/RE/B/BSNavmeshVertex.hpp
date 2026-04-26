#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSNavmeshVertex
	{
	public:
		// members
		NiPoint3 location; // 00
	};
	static_assert(sizeof(BSNavmeshVertex) == 0x0C);
}

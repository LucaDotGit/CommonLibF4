#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSNavmeshVertex
	{
	public:
		// members
		NiPoint3 location; // 0x00
	};

	static_assert(sizeof(BSNavmeshVertex) == 0x0C);
}

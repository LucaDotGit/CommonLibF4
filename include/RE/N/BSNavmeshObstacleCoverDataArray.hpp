#pragma once

#include "RE/B/BSTArrayRefCounted.hpp"
#include "RE/N/BSNavmeshObstacleCoverData.hpp"

namespace RE
{
	class BSNavmeshCoverEdge;

	class BSNavmeshObstacleCoverDataArray
		: public BSTArrayRefCounted<BSNavmeshObstacleCoverData> // 00
	{
	public:
	};
	static_assert(sizeof(BSNavmeshObstacleCoverDataArray) == 0x20);
}

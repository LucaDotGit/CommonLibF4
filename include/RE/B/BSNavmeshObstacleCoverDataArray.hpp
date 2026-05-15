#pragma once

#include "RE/B/BSNavmeshObstacleCoverData.hpp"
#include "RE/B/BSTArrayRefCounted.hpp"

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

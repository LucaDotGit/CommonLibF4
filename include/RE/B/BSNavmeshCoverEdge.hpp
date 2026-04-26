#pragma once

#include "RE/B/BSNavmeshCoverEdgeBase.hpp"

namespace RE
{
	class BSNavmeshCoverEdge
		: public BSNavmeshCoverEdgeBase // 00
	{
	public:
		// members
		std::array<std::uint16_t, 2> vertexArray; // 00
		std::uint32_t data;						  // 04
	};
	static_assert(sizeof(BSNavmeshCoverEdge) == 0x08);
}

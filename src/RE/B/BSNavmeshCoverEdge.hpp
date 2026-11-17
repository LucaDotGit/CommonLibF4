#pragma once

#include "RE/B/BSNavmeshCoverEdgeBase.hpp"

namespace RE
{
	class BSNavmeshCoverEdge : public BSNavmeshCoverEdgeBase // 0x00
	{
	public:
		// members
		std::array<std::uint16_t, 2> vertexArray; // 0x00
		std::uint32_t data;						  // 0x04
	};

	static_assert(sizeof(BSNavmeshCoverEdge) == 0x08);
}

#pragma once

#include "RE/B/BSNavmeshTriangleEdgePortal.hpp"

namespace RE
{
	enum class EDGE_EXTRA_INFO_TYPE : std::int32_t;

	class BSNavmeshEdgeExtraInfo
	{
	public:
		// members
		REX::Enum<EDGE_EXTRA_INFO_TYPE, std::int32_t> type; // 0x00
		BSNavmeshTriangleEdgePortal portal;					// 0x04
	};

	static_assert(sizeof(BSNavmeshEdgeExtraInfo) == 0x0C);
}

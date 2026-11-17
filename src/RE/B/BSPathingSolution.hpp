#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSVirtualPathingNode.hpp"

namespace RE
{
	class BSPathingNode;

	class BSPathingSolution : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSTSmallArray<BSVirtualPathingNode, 2> virtualPathingNodes; // 0x08
		std::int32_t firstLoadedVirtualNodeIndex;					// 0x88
		std::int32_t lastLoadedVirtualNodeIndex;					// 0x8C
		BSTArray<BSPathingNode> currentPathingNodes;				// 0x90
		REX::Float32 goalRadius;									// 0xA8
		bool incompletePath;										// 0xAC
		bool requestGoalUnused;										// 0xAD
	};

	static_assert(sizeof(BSPathingSolution) == 0xB0);
}

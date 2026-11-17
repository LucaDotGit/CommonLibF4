#pragma once

#include "RE/B/BSPathingLocation.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class MovementMessage;

	class BSVirtualPathingNode
	{
	public:
		// members
		BSPathingLocation location;					   // 0x000
		BSTSmartPointer<MovementMessage> actionAtNode; // 0x030
	};

	static_assert(sizeof(BSVirtualPathingNode) == 0x38);
}

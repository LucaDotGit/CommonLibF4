#pragma once

#include "RE/B/BSPathingLocation.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class MovementMessage;

	class BSPathingNode
	{
	public:
		// members
		BSPathingLocation location;					   // 0x00
		BSTSmartPointer<MovementMessage> actionAtNode; // 0x30
		NiPoint3 tangent;							   // 0x38
	};

	static_assert(sizeof(BSPathingNode) == 0x48);
}

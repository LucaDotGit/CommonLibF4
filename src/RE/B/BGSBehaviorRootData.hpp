#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/S/SubgraphIdentifier.hpp"

namespace RE
{
	class BGSBehaviorRootData
	{
	public:
		// members
		BSFixedString idleManagerRootToUse; // 0x00
		BSFixedString behaviorRootFilename; // 0x08
		SubgraphIdentifier identifier;		// 0x10
		bool firstPerson;					// 0x18
	};

	static_assert(sizeof(BGSBehaviorRootData) == 0x20);
}

#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/S/SubgraphIdentifier.hpp"

namespace RE
{
	class BGSBehaviorRootData
	{
	public:
		// members
		BSFixedString idleManagerRootToUse; // 00
		BSFixedString behaviorRootFilename; // 08
		SubgraphIdentifier identifier;		// 10
		bool firstPerson;					// 18
	};
	static_assert(sizeof(BGSBehaviorRootData) == 0x20);
}

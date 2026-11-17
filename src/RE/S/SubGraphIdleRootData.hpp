#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/S/SubgraphIdentifier.hpp"

namespace RE
{
	class SubGraphIdleRootData
	{
	public:
		// members
		SubgraphIdentifier subGraphID; // 0x00
		BSFixedString idleRootName;	   // 0x08
		std::int8_t count;			   // 0x10
		std::int8_t activeCount;	   // 0x11
		bool forFirstPerson;		   // 0x12
	};

	static_assert(sizeof(SubGraphIdleRootData) == 0x18);
}

#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::nsHUDTypes
{
	class ObjectiveData
	{
	public:
		// members
		BSFixedStringCS objectiveName; // 0x00
		bool completed;				   // 0x08
		bool orWithPrevious;		   // 0x09
	};

	static_assert(sizeof(ObjectiveData) == 0x10);
}

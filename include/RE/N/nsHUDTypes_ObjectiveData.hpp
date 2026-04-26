#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::nsHUDTypes
{
	class ObjectiveData
	{
	public:
		// members
		BSFixedStringCS objectiveName; // 00
		bool completed;				   // 08
		bool orWithPrevious;		   // 09
	};
	static_assert(sizeof(ObjectiveData) == 0x10);
}

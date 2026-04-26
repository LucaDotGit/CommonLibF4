#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSStoryEventMember;

	class BGSRegisteredStoryEvent
	{
	public:
		// members
		std::uint32_t uniqueID;					// 00
		BSTArray<BGSStoryEventMember>* members; // 08
		BSString name;							// 10
		bool immediate;							// 18
	};
	static_assert(sizeof(BGSRegisteredStoryEvent) == 0x28);
}

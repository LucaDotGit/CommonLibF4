#pragma once

#include "RE/B/BSString.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSStoryEventMember;

	class BGSRegisteredStoryEvent
	{
	public:
		// members
		std::uint32_t uniqueID;					// 0x00
		BSTArray<BGSStoryEventMember>* members; // 0x08
		BSString name;							// 0x10
		bool immediate;							// 0x18
	};

	static_assert(sizeof(BGSRegisteredStoryEvent) == 0x28);
}

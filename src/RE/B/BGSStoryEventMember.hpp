#pragma once

#include "RE/B/BSString.hpp"

namespace RE
{
	class BGSStoryEventMember
	{
	public:
		enum class DATA_TYPE : std::int32_t; // To-Do

		// members
		REX::Enum<DATA_TYPE, std::int32_t> type; // 0x00
		std::uint32_t uniqueID;					 // 0x04
		BSString name;							 // 0x08
	};

	static_assert(sizeof(BGSStoryEventMember) == 0x18);
}

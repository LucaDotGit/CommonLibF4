#pragma once

#include "RE/B/BSStringT.hpp"

namespace RE
{
	class BGSStoryEventMember
	{
	public:
		enum class DATA_TYPE : std::int32_t; // TODO

		// members
		REX::Enum<DATA_TYPE, std::int32_t> type; // 00
		std::uint32_t uniqueID;					 // 04
		BSString name;							 // 08
	};
	static_assert(sizeof(BGSStoryEventMember) == 0x18);
}

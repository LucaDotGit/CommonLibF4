#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class StringFileInfo;

	class BGSLocalizedStringIL
	{
	public:
		[[nodiscard]] static BSTHashMap<BSFixedString, StringFileInfo*>& GetStringInfoMap()
		{
			static const auto STRING_FILE_INFO_MAP = REL::Relocation<BSTHashMap<BSFixedString, StringFileInfo*>*>{ ID::BGSLocalizedStringIL::StringInfoMap, Offset::BGSLocalizedStringIL::StringInfoMap };
			return *STRING_FILE_INFO_MAP;
		}

		// members
		BSFixedStringCS string; // 00
	};
	static_assert(sizeof(BGSLocalizedStringIL) == 0x08);
}

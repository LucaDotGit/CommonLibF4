#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class PersistentStringInfo;
}

namespace RE::BGSLocalizedStringPL
{
	[[nodiscard]]
	inline auto GetStringInfoMap() noexcept -> BSTHashMap<BSFixedString, PersistentStringInfo*>&
	{
		static const auto STRING_FILE_INFO_MAP = REL::Relocation<BSTHashMap<BSFixedString, PersistentStringInfo*>*>{
			ID::BGSLocalizedStringPL::StringInfoMap,
			Offset::BGSLocalizedStringPL::StringInfoMap
		};
		return *STRING_FILE_INFO_MAP;
	}
}

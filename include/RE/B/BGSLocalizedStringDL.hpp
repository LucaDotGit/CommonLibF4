#pragma once

#include "RE/B/BGSLocalizedStrings.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE
{
	class StringFileInfo;
	class TESFile;

	class BGSLocalizedStringDL
	{
	public:
		[[nodiscard]] static BSTHashMap<BSFixedString, StringFileInfo*>& GetStringInfoMap()
		{
			static const auto STRING_FILE_INFO_MAP = REL::Relocation<BSTHashMap<BSFixedString, StringFileInfo*>*>{ ID::BGSLocalizedStringDL::StringInfoMap, Offset::BGSLocalizedStringDL::StringInfoMap };
			return *STRING_FILE_INFO_MAP;
		}

		[[nodiscard]] BGSLocalizedStrings::ScrapStringBuffer&& GetText(TESFile& a_file) const
		{
			using FuncType = decltype(&BGSLocalizedStringDL::GetText);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSLocalizedStringDL::GetText };
			return std::invoke(FUNC, this, a_file);
		}

		// members
		std::uint32_t id; // 00
	};
	static_assert(sizeof(BGSLocalizedStringDL) == 0x04);
}

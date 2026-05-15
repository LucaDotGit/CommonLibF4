#include "RE/B/BGSTypedKeywordValue.hpp"

#include "RE/B/BGSKeyword.hpp"

namespace RE::Impl
{
	BGSKeyword* GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index)
	{
		return BGSKeyword::GetTypedKeywordByIndex(a_type, a_index);
	}

	auto GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type)
		-> std::optional<std::uint16_t>
	{
		return BGSKeyword::GetIndexForTypedKeyword(a_keyword, a_type);
	}
}

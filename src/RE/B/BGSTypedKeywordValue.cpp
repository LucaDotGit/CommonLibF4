#include "RE/B/BGSTypedKeywordValue.hpp"

#include "RE/B/BGSKeyword.hpp"

namespace RE::Impl
{
	auto GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index) noexcept -> BGSKeyword*
	{
		return BGSKeyword::GetTypedKeywordByIndex(a_type, a_index);
	}

	auto GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type) noexcept
		-> std::optional<std::uint16_t>
	{
		return BGSKeyword::GetIndexForTypedKeyword(a_keyword, a_type);
	}
}

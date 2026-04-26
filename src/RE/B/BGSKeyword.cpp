#include "RE/B/BGSKeyword.hpp"

namespace RE
{
	auto BGSKeyword::GetTypedKeywords() -> std::span<BSTArray<BGSKeyword*>, std::to_underlying(KeywordType::kTotal)>
	{
		static const auto TYPED_KEYWORDS = REL::Relocation<std::array<BSTArray<BGSKeyword*>, std::to_underlying(KeywordType::kTotal)>*>{ ID::BGSKeyword::TypedKeywords };
		return { *TYPED_KEYWORDS };
	}

	auto BGSKeyword::GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type) -> std::optional<std::uint16_t>
	{
		REX::Assert(a_type >= KeywordType::kNone && a_type < KeywordType::kTotal);

		const auto keywords = GetTypedKeywords();
		const auto& array = keywords[std::to_underlying(a_type)];

		for (auto i = 0ui16; i < static_cast<std::uint16_t>(array.size()); i++) {
			if (array[i] == a_keyword) {
				return i;
			}
		}

		return std::nullopt;
	}

	BGSKeyword* BGSKeyword::GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index)
	{
		REX::Assert(a_type >= KeywordType::kNone && a_type < KeywordType::kTotal);

		const auto keywords = GetTypedKeywords();
		const auto& array = keywords[std::to_underlying(a_type)];
		return a_index < array.size() ? array[a_index] : nullptr;
	}
}

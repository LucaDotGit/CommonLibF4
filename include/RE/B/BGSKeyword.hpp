#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/K/KeywordType.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSKeyword
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSKeyword };
		inline static constexpr auto VTABLE{ VTABLE::BGSKeyword };
		inline static constexpr auto FORM_TYPE{ FormType::kKeyword };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kRestricted = 1 << 15
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]] static auto GetTypedKeywords() -> std::span<BSTArray<BGSKeyword*>, std::to_underlying(KeywordType::kTotal)>;

		[[nodiscard]] static auto GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type) -> std::optional<std::uint16_t>;
		[[nodiscard]] static BGSKeyword* GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index);

		// members
		BSFixedString formEditorID; // 20
	};
	static_assert(sizeof(BGSKeyword) == 0x28);
}

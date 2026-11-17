#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/K/KeywordType.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSKeyword : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSKeyword;
		inline static constexpr const auto& VTABLE = VTABLE::BGSKeyword;
		inline static constexpr auto FORM_TYPE = FormType::Keyword;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				Restricted = 1 << 15
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]]
		static auto GetTypedKeywords() noexcept
			-> std::span<BSTArray<BGSKeyword*>, std::to_underlying(KeywordType::_Count)>;

		[[nodiscard]]
		static auto GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type) noexcept
			-> std::optional<std::uint16_t>;
		[[nodiscard]]
		static auto GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index) noexcept -> BGSKeyword*;

		// members
		BSFixedString formEditorID; // 0x20
	};

	static_assert(sizeof(BGSKeyword) == 0x28);
}

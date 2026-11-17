#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/K/KeywordType.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE::Impl
{
	[[nodiscard]]
	auto GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index) noexcept -> BGSKeyword*;
	[[nodiscard]]
	auto GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type) noexcept
		-> std::optional<std::uint16_t>;
}

namespace RE
{
	template <KeywordType T>
	class BGSTypedKeywordValue
	{
	public:
		inline static constexpr auto KEYWORD_TYPE = T;

		GAME_HEAP_REDEFINE_NEW(BGSTypedKeywordValue);

		[[nodiscard]]
		auto GetKeyword() const -> BGSKeyword*
		{
			return Impl::GetTypedKeywordByIndex(T, keywordIndex);
		}

		auto SetKeyword(const BGSKeyword* a_keyword) -> bool
		{
			auto index = Impl::GetIndexForTypedKeyword(a_keyword, T);
			if (!index.has_value()) {
				return false;
			}

			keywordIndex = index.value();
			return true;
		}

		// members
		std::uint16_t keywordIndex; // 0x00
	};

	template <KeywordType T>
	class BGSTypedKeywordValueArray
	{
	public:
		inline static constexpr auto KEYWORD_TYPE = T;

		GAME_HEAP_REDEFINE_NEW(BGSTypedKeywordValueArray);

		[[nodiscard]]
		auto ContainsKeyword(const BGSKeyword* a_keyword) const -> bool
		{
			if (!array || !a_keyword) {
				return false;
			}

			for (auto i = static_cast<std::uint32_t>(0); i < size; i++) {
				const auto* keyword = Impl::GetTypedKeywordByIndex(T, array[i].keywordIndex);
				if (keyword == a_keyword) {
					return true;
				}
			}

			return false;
		}

		[[nodiscard]]
		auto GetKeywords() const -> std::optional<BSTArray<BGSKeyword*>>
		{
			if (!array) {
				return std::nullopt;
			}

			auto result = BSTArray<BGSKeyword*>();
			result.reserve(size);

			for (auto i = static_cast<std::uint32_t>(0); i < size; i++) {
				auto* keyword = Impl::GetTypedKeywordByIndex(T, array[i].keywordIndex);
				if (keyword) {
					result.push_back(keyword);
				}
			}

			return result;
		}

		void SetKeywords(std::span<BGSKeyword* const> a_keywords)
		{
			size = 0;
			array.deallocate_bytes();

			if (a_keywords.empty()) {
				return;
			}

			const auto newSize = static_cast<std::uint32_t>(a_keywords.size());
			auto* newArray = SimpleArray<BGSTypedKeywordValue<KEYWORD_TYPE>>(newSize);

			for (auto i = static_cast<std::uint32_t>(0); i < newSize; i++) {
				auto keywordIndex = Impl::GetIndexForTypedKeyword(a_keywords[i], KEYWORD_TYPE);
				newArray[i].keywordIndex =
					keywordIndex.value_or(std::numeric_limits<decltype(keywordIndex)::value_type>::max());
			}

			array = std::move(newArray);
			size = static_cast<std::uint32_t>(newSize);
		}

		void Clear()
		{
			size = 0;
			array.deallocate_bytes();
		}

		// members
		SimpleArray<BGSTypedKeywordValue<KEYWORD_TYPE>> array; // 0x00
		std::uint32_t size;									   // 0x08
	};
}

#pragma once

#include "RE/K/KeywordType.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE::Impl
{
	[[nodiscard]] BGSKeyword* GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index);
	[[nodiscard]] auto GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type)
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

		[[nodiscard]] BGSKeyword* GetKeyword() const
		{
			return Impl::GetTypedKeywordByIndex(T, keywordIndex);
		}

		bool SetKeyword(const BGSKeyword* a_keyword)
		{
			auto index = Impl::GetIndexForTypedKeyword(a_keyword, T);
			if (!index) {
				return false;
			}

			keywordIndex = *index;
			return true;
		}

		// members
		std::uint16_t keywordIndex; // 00
	};

	template <KeywordType T>
	class BGSTypedKeywordValueArray
	{
	public:
		inline static constexpr auto KEYWORD_TYPE = T;

		GAME_HEAP_REDEFINE_NEW(BGSTypedKeywordValueArray);

		[[nodiscard]] bool ContainsKeyword(const BGSKeyword* a_keyword) const
		{
			if (!array || !a_keyword) {
				return false;
			}

			for (auto i = 0ui32; i < size; i++) {
				const auto* keyword = Impl::GetTypedKeywordByIndex(T, array[i].keywordIndex);
				if (keyword == a_keyword) {
					return true;
				}
			}

			return false;
		}

		[[nodiscard]] auto GetKeywords() const
			-> std::optional<std::vector<BGSKeyword*>>
		{
			if (!array) {
				return std::nullopt;
			}

			auto result = std::vector<BGSKeyword*>();
			result.reserve(size);

			for (auto i = 0ui32; i < size; i++) {
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

			for (auto i = 0ui32; i < newSize; i++) {
				auto keywordIndex = Impl::GetIndexForTypedKeyword(a_keywords[i], KEYWORD_TYPE);
				newArray[i].keywordIndex = keywordIndex.value_or(std::numeric_limits<decltype(keywordIndex)::value_type>::max());
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
		SimpleArray<BGSTypedKeywordValue<KEYWORD_TYPE>> array; // 00
		std::uint32_t size;									   // 08
	};
}

#include "RE/B/BGSKeywordForm.hpp"

#include "RE/B/BGSKeyword.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	auto BGSKeywordForm::ContainsKeyword(const BGSKeyword* a_keyword) const noexcept -> bool
	{
		if (!a_keyword) {
			return false;
		}

		return ForEachKeyword([a_keyword](const BGSKeyword* a_current) noexcept -> BSContainer::ForEachResult {
				   if (a_current == a_keyword) {
					   return BSContainer::ForEachResult::Stop;
				   }

				   return BSContainer::ForEachResult::Continue;
			   }) == BSContainer::ForEachResult::Stop;
	}

	auto BGSKeywordForm::ContainsPartialKeywordString(std::string_view a_editorID) const noexcept -> bool
	{
		return ForEachKeyword([a_editorID](const BGSKeyword* a_keyword) noexcept -> BSContainer::ForEachResult {
				   if (a_keyword->formEditorID.contains(a_editorID)) {
					   return BSContainer::ForEachResult::Stop;
				   }

				   return BSContainer::ForEachResult::Continue;
			   }) == BSContainer::ForEachResult::Stop;
	}

	auto BGSKeywordForm::ContainsExactKeywordString(std::string_view a_editorID) const noexcept -> bool
	{
		return ForEachKeyword([a_editorID](const BGSKeyword* a_keyword) noexcept -> BSContainer::ForEachResult {
				   if (a_keyword->formEditorID == a_editorID) {
					   return BSContainer::ForEachResult::Stop;
				   }

				   return BSContainer::ForEachResult::Continue;
			   }) == BSContainer::ForEachResult::Stop;
	}

	auto BGSKeywordForm::GetKeywordCount() const noexcept -> std::uint32_t
	{
		return numKeywords;
	}

	auto BGSKeywordForm::GetKeywordIndex(const BGSKeyword* a_keyword) const noexcept -> std::optional<std::uint32_t>
	{
		for (auto i = static_cast<std::uint32_t>(0); i < numKeywords; i++) {
			if (keywords[i] == a_keyword) {
				return i;
			}
		}

		return std::nullopt;
	}

	auto BGSKeywordForm::GetKeywords() noexcept -> std::span<BGSKeyword*>
	{
		return {keywords.data(), numKeywords};
	}

	auto BGSKeywordForm::GetKeywords() const noexcept -> std::span<BGSKeyword* const>
	{
		return {keywords.data(), numKeywords};
	}

	void BGSKeywordForm::SetKeywords(std::span<BGSKeyword*> a_keywords)
	{
		auto newCount = static_cast<std::uint32_t>(a_keywords.size());
		auto newData = SimpleArray<BGSKeyword*>(newCount);
		std::ranges::copy(a_keywords, newData.data());

		keywords = std::move(newData);
		numKeywords = newCount;
	}

	auto BGSKeywordForm::GetNthKeyword(std::uint32_t a_index) const noexcept -> BGSKeyword*
	{
		return a_index < numKeywords ? keywords[a_index] : nullptr;
	}

	auto BGSKeywordForm::SetNthKeyword(std::uint32_t a_index, BGSKeyword* a_keyword) -> bool
	{
		if (a_index >= numKeywords) {
			return false;
		}

		keywords[a_index] = a_keyword;
		return true;
	}

	auto BGSKeywordForm::RemoveNthKeyword(std::uint32_t a_index) -> bool
	{
		if (a_index >= numKeywords) {
			return false;
		}

		auto newCount = numKeywords - 1;
		auto newData = SimpleArray<BGSKeyword*>(newCount);

		for (auto i = static_cast<std::uint32_t>(0); i < a_index; i++) {
			newData[i] = keywords[i];
		}

		for (auto i = a_index + 1; i < numKeywords; i++) {
			newData[i - 1] = keywords[i];
		}

		keywords = std::move(newData);
		numKeywords = newCount;
		return true;
	}

	auto BGSKeywordForm::AddKeyword(BGSKeyword* a_keyword) -> bool
	{
		if (!a_keyword || ContainsKeyword(a_keyword)) {
			return false;
		}

		auto newCount = numKeywords + 1;
		auto newData = SimpleArray<BGSKeyword*>(newCount);

		std::ranges::copy(keywords.data(), keywords.data() + numKeywords, newData.data());
		newData[numKeywords] = a_keyword;

		keywords = std::move(newData);
		numKeywords = newCount;
		return true;
	}

	auto BGSKeywordForm::RemoveKeyword(BGSKeyword* a_keyword) -> bool
	{
		const auto index = GetKeywordIndex(a_keyword);
		return index && RemoveNthKeyword(*index);
	}

	auto BGSKeywordForm::ReplaceKeyword(BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword) -> bool
	{
		if (!a_oldKeyword || !a_newKeyword) {
			return false;
		}

		const auto index = GetKeywordIndex(a_oldKeyword);
		if (!index.has_value()) {
			return false;
		}

		keywords[index.value()] = a_newKeyword;
		return true;
	}

	auto BGSKeywordForm::AddKeywords(std::span<BGSKeyword*> a_keywords) -> bool
	{
		if (a_keywords.empty()) {
			return false;
		}

		auto newCount = numKeywords + static_cast<std::uint32_t>(a_keywords.size());
		auto newData = SimpleArray<BGSKeyword*>(newCount);

		std::ranges::copy(keywords.data(), keywords.data() + numKeywords, newData.data());
		std::ranges::copy(a_keywords, newData.data() + numKeywords);

		keywords = std::move(newData);
		numKeywords = newCount;
		return true;
	}

	auto BGSKeywordForm::RemoveKeywords(std::span<BGSKeyword*> a_keywords) -> bool
	{
		if (a_keywords.empty()) {
			return false;
		}

		auto removedIndexes =
			std::flat_set<std::uint32_t, std::less<>, std::vector<std::uint32_t, StlAllocator<std::uint32_t>>>();
		REX::Reserve(removedIndexes, a_keywords.size());

		for (auto* keyword : a_keywords) {
			const auto index = GetKeywordIndex(keyword);
			if (index) {
				removedIndexes.insert(*index);
			}
		}

		if (removedIndexes.empty()) {
			return false;
		}

		auto newCount = numKeywords - static_cast<std::uint32_t>(removedIndexes.size());
		auto newData = SimpleArray<BGSKeyword*>(newCount);

		for (auto i = static_cast<std::uint32_t>(0), j = static_cast<std::uint32_t>(0); i < numKeywords; i++) {
			if (removedIndexes.contains(i)) {
				continue;
			}

			newData[j++] = keywords[i];
		}

		keywords = std::move(newData);
		numKeywords = newCount;
		return true;
	}

	void BGSKeywordForm::ClearKeywords() noexcept
	{
		keywords.deallocate_bytes();
		numKeywords = 0;
	}

	auto BGSKeywordForm::ForEachKeyword(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		if (!keywords.data()) {
			return BSContainer::ForEachResult::Continue;
		}

		for (auto i = static_cast<std::uint32_t>(0); i < numKeywords; i++) {
			auto* keyword = keywords[i];
			if (std::invoke(a_predicate.get(), keyword) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}

#include "RE/B/BGSKeywordForm.hpp"

#include "RE/B/BGSKeyword.hpp"
#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	bool BGSKeywordForm::ContainsKeyword(const BGSKeyword* a_keyword) const
	{
		if (!a_keyword) {
			return false;
		}

		return ForEachKeyword([a_keyword](const BGSKeyword* a_current) {
			if (a_current == a_keyword) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kStop;
	}

	bool BGSKeywordForm::ContainsPartialKeywordString(std::string_view a_editorID) const
	{
		return ForEachKeyword([a_editorID](const BGSKeyword* a_keyword) {
			if (a_keyword->formEditorID.contains(a_editorID)) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kStop;
	}

	bool BGSKeywordForm::ContainsExactKeywordString(std::string_view a_editorID) const
	{
		return ForEachKeyword([a_editorID](const BGSKeyword* a_keyword) {
			if (a_keyword->formEditorID == a_editorID) {
				return BSContainer::ForEachResult::kStop;
			}

			return BSContainer::ForEachResult::kContinue;
		}) == BSContainer::ForEachResult::kStop;
	}

	std::uint32_t BGSKeywordForm::GetKeywordCount() const noexcept
	{
		return numKeywords;
	}

	auto BGSKeywordForm::GetKeywordIndex(const BGSKeyword* a_keyword) const -> std::optional<std::uint32_t>
	{
		for (auto i = 0ui32; i < numKeywords; i++) {
			if (keywords[i] == a_keyword) {
				return i;
			}
		}

		return std::nullopt;
	}

	std::span<BGSKeyword*> BGSKeywordForm::GetKeywords() noexcept
	{
		return { keywords.data(), numKeywords };
	}

	std::span<BGSKeyword* const> BGSKeywordForm::GetKeywords() const noexcept
	{
		return { keywords.data(), numKeywords };
	}

	void BGSKeywordForm::SetKeywords(std::span<BGSKeyword*> a_keywords)
	{
		auto newCount = static_cast<std::uint32_t>(a_keywords.size());
		auto newData = SimpleArray<BGSKeyword*>(newCount);
		std::ranges::copy(a_keywords, newData.data());

		keywords = std::move(newData);
		numKeywords = newCount;
	}

	BGSKeyword* BGSKeywordForm::GetNthKeyword(std::uint32_t a_index) const
	{
		return a_index < numKeywords ? keywords[a_index] : nullptr;
	}

	bool BGSKeywordForm::SetNthKeyword(std::uint32_t a_index, BGSKeyword* a_keyword)
	{
		if (a_index >= numKeywords) {
			return false;
		}

		keywords[a_index] = a_keyword;
		return true;
	}

	bool BGSKeywordForm::RemoveNthKeyword(std::uint32_t a_index)
	{
		if (a_index >= numKeywords) {
			return false;
		}

		auto newCount = numKeywords - 1;
		auto newData = SimpleArray<BGSKeyword*>(newCount);

		for (auto i = 0ui32; i < a_index; i++) {
			newData[i] = keywords[i];
		}

		for (auto i = a_index + 1; i < numKeywords; i++) {
			newData[i - 1] = keywords[i];
		}

		keywords = std::move(newData);
		numKeywords = newCount;
		return true;
	}

	bool BGSKeywordForm::AddKeyword(BGSKeyword* a_keyword)
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

	bool BGSKeywordForm::RemoveKeyword(BGSKeyword* a_keyword)
	{
		const auto index = GetKeywordIndex(a_keyword);
		return index && RemoveNthKeyword(*index);
	}

	bool BGSKeywordForm::ReplaceKeyword(BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword)
	{
		if (!a_oldKeyword || !a_newKeyword) {
			return false;
		}

		const auto index = GetKeywordIndex(a_oldKeyword);
		if (!index) {
			return false;
		}

		keywords[*index] = a_newKeyword;
		return true;
	}

	bool BGSKeywordForm::AddKeywords(std::span<BGSKeyword*> a_keywords)
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

	bool BGSKeywordForm::RemoveKeywords(std::span<BGSKeyword*> a_keywords)
	{
		if (a_keywords.empty()) {
			return false;
		}

		auto removedIndexes = std::unordered_set<std::uint32_t>();
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

		for (auto i = 0ui32, j = 0ui32; i < numKeywords; i++) {
			if (removedIndexes.contains(i)) {
				continue;
			}

			newData[j++] = keywords[i];
		}

		keywords = std::move(newData);
		numKeywords = newCount;
		return true;
	}

	void BGSKeywordForm::ClearKeywords()
	{
		keywords.deallocate_bytes();
		numKeywords = 0;
	}

	BSContainer::ForEachResult BGSKeywordForm::ForEachKeyword(
		const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate) const
	{
		if (!keywords.data()) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (auto i = 0ui32; i < numKeywords; i++) {
			auto* keyword = keywords[i];
			if (keyword && std::invoke(*a_predicate, keyword) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}

#include "RE/B/BGSConstructibleObject.hpp"

#include "RE/S/SimpleArray.hpp"

namespace RE
{
	auto BGSConstructibleObject::GetRecipeKeywords() const -> BSTArray<BGSKeyword*>
	{
		if (!filterKeywords.array || filterKeywords.size == 0) {
			return {};
		}

		auto keywords = BSTArray<BGSKeyword*>();
		keywords.reserve(filterKeywords.size);

		for (auto i = static_cast<std::uint32_t>(0); i < filterKeywords.size; i++) {
			auto* keyword = Impl::GetTypedKeywordByIndex(ObjectKeywordType, filterKeywords.array[i].keywordIndex);
			keywords.push_back(keyword);
		}

		return keywords;
	}

	void BGSConstructibleObject::SetRecipeKeywords(std::span<BGSKeyword*> a_keywords)
	{
		auto& oldArray = filterKeywords.array;
		if (oldArray) {
			oldArray.deallocate_bytes();
		}

		auto newSize = static_cast<std::uint32_t>(a_keywords.size());
		auto newArray = SimpleArray<BGSTypedKeywordValue<ObjectKeywordType>>(newSize);

		for (auto i = static_cast<std::uint32_t>(0); i < newSize; i++) {
			const auto index = Impl::GetIndexForTypedKeyword(a_keywords[i], ObjectKeywordType);
			newArray[i].keywordIndex = index.value_or(std::numeric_limits<std::uint16_t>::max());
		}

		filterKeywords.size = newSize;
		filterKeywords.array = std::move(newArray);
	}

	auto BGSConstructibleObject::GetComponents() const noexcept
		-> std::optional<std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>>
	{
		const auto* objectComponents = requiredItems;
		if (!objectComponents) {
			return std::nullopt;
		}

		return *requiredItems;
	}

	void BGSConstructibleObject::SetComponents(
		std::span<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>> a_components)
	{
		if (requiredItems) {
			delete requiredItems;
			requiredItems = nullptr;
		}

		if (a_components.empty()) {
			return;
		}

		requiredItems =
			new BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>{a_components.begin(), a_components.end()};
	}
}

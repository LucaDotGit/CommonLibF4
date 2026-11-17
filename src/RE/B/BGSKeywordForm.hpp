#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BaseFormComponent.hpp"
#include "RE/I/IKeywordFormBase.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class TBO_InstanceData;

	class __declspec(novtable) BGSKeywordForm :
		public BaseFormComponent, // 0x00
		public IKeywordFormBase	  // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSKeywordForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSKeywordForm;

		~BGSKeywordForm() override; // 0x00

		// override (BaseFormComponent)
		auto GetFormComponentType() const -> std::uint32_t override;			  // 0x01
		void InitializeDataComponent() override;								  // 0x02
		void ClearDataComponent() override;										  // 0x03
		void InitComponent() override;											  // 0x04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 0x05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 0x06

		// override (IKeywordFormBase)
		auto HasKeyword(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data = nullptr) const
			-> bool override; // 0x01
		void CollectAllKeywords(BSScrapArray<const BGSKeyword*>& a_outKeywords, const TBO_InstanceData* a_instanceData)
			const override; // 0x02

		// add
		virtual auto GetDefaultKeyword() const -> BGSKeyword*; // 0x07 - { return nullptr; }

		[[nodiscard]]
		auto ContainsKeyword(const BGSKeyword* a_keyword) const noexcept -> bool;
		[[nodiscard]]
		auto ContainsPartialKeywordString(std::string_view a_editorID) const noexcept -> bool;
		[[nodiscard]]
		auto ContainsExactKeywordString(std::string_view a_editorID) const noexcept -> bool;

		[[nodiscard]]
		auto GetKeywordCount() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetKeywordIndex(const BGSKeyword* a_keyword) const noexcept -> std::optional<std::uint32_t>;

		[[nodiscard]]
		auto GetKeywords() noexcept -> std::span<BGSKeyword*>;
		[[nodiscard]]
		auto GetKeywords() const noexcept -> std::span<BGSKeyword* const>;
		void SetKeywords(std::span<BGSKeyword*> a_keywords);

		[[nodiscard]]
		auto GetNthKeyword(std::uint32_t a_index) const noexcept -> BGSKeyword*;
		auto SetNthKeyword(std::uint32_t a_index, BGSKeyword* a_keyword) -> bool;
		auto RemoveNthKeyword(std::uint32_t a_index) -> bool;

		auto AddKeyword(BGSKeyword* a_keyword) -> bool;
		auto RemoveKeyword(BGSKeyword* a_keyword) -> bool;
		auto ReplaceKeyword(BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword) -> bool;

		auto AddKeywords(std::span<BGSKeyword*> a_keywords) -> bool;
		auto RemoveKeywords(std::span<BGSKeyword*> a_keywords) -> bool;

		void ClearKeywords() noexcept;

		auto ForEachKeyword(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate)
			const -> BSContainer::ForEachResult;

		// members
		SimpleArray<BGSKeyword*> keywords; // 0x10
		std::uint32_t numKeywords;		   // 0x18
	};

	static_assert(sizeof(BGSKeywordForm) == 0x20);
}

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

	class __declspec(novtable) BGSKeywordForm
		: public BaseFormComponent, // 00
		  public IKeywordFormBase	// 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSKeywordForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSKeywordForm };

		~BGSKeywordForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;					  // 01
		void InitializeDataComponent() override;								  // 02
		void ClearDataComponent() override;										  // 03
		void InitComponent() override;											  // 04
		void CopyComponent(BaseFormComponent* a_copy) override;					  // 05
		void CopyComponent(BaseFormComponent* a_copy, TESForm* a_owner) override; // 06

		// override (IKeywordFormBase)
		bool HasKeyword(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data = nullptr) const override;							// 01
		void CollectAllKeywords(BSScrapArray<const BGSKeyword*>& a_outKeywords, const TBO_InstanceData* a_instanceData) const override; // 02

		// add
		virtual BGSKeyword* GetDefaultKeyword() const; // 07 - { return nullptr; }

		[[nodiscard]] bool ContainsKeyword(const BGSKeyword* a_keyword) const;
		[[nodiscard]] bool ContainsPartialKeywordString(std::string_view a_editorID) const;
		[[nodiscard]] bool ContainsExactKeywordString(std::string_view a_editorID) const;

		[[nodiscard]] std::uint32_t GetKeywordCount() const noexcept;
		[[nodiscard]] auto GetKeywordIndex(const BGSKeyword* a_keyword) const -> std::optional<std::uint32_t>;

		[[nodiscard]] std::span<BGSKeyword*> GetKeywords() noexcept;
		[[nodiscard]] std::span<BGSKeyword* const> GetKeywords() const noexcept;
		void SetKeywords(std::span<BGSKeyword*> a_keywords);

		[[nodiscard]] BGSKeyword* GetNthKeyword(std::uint32_t a_index) const;
		bool SetNthKeyword(std::uint32_t a_index, BGSKeyword* a_keyword);
		bool RemoveNthKeyword(std::uint32_t a_index);

		bool AddKeyword(BGSKeyword* a_keyword);
		bool RemoveKeyword(BGSKeyword* a_keyword);
		bool ReplaceKeyword(BGSKeyword* a_oldKeyword, BGSKeyword* a_newKeyword);

		bool AddKeywords(std::span<BGSKeyword*> a_keywords);
		bool RemoveKeywords(std::span<BGSKeyword*> a_keywords);

		void ClearKeywords();

		BSContainer::ForEachResult ForEachKeyword(
			const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate) const;

		// members
		SimpleArray<BGSKeyword*> keywords; // 10
		std::uint32_t numKeywords;		   // 18
	};
	static_assert(sizeof(BGSKeywordForm) == 0x20);
}

#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSListForm
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSListForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSListForm };
		inline static constexpr auto FORM_TYPE{ FormType::kFormList };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kAddedForm = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]] std::uint32_t GetFormCount() const noexcept;
		[[nodiscard]] std::uint32_t GetEditorFormCount() const noexcept;
		[[nodiscard]] std::uint32_t GetScriptFormCount() const noexcept;

		[[nodiscard]] std::vector<TESForm*> GetAllForms() const;

		[[nodiscard]] auto GetScriptForms() const
			-> std::optional<std::vector<TESForm*>>;
		void SetScriptForms(std::span<TESForm*> a_forms);

		[[nodiscard]] bool ContainsForm(const TESForm* a_form) const;
		[[nodiscard]] bool ContainsEditorForm(const TESForm* a_form) const;
		[[nodiscard]] bool ContainsScriptForm(const TESForm* a_form) const;

		[[nodiscard]] auto GetFormIndex(const TESForm* a_form) const
			-> std::optional<std::uint32_t>;
		[[nodiscard]] auto GetEditorFormIndex(const TESForm* a_form) const
			-> std::optional<std::uint32_t>;
		[[nodiscard]] auto GetScriptFormIndex(const TESForm* a_form) const
			-> std::optional<std::uint32_t>;

		[[nodiscard]] TESForm* GetNthForm(std::uint32_t a_index) const;
		bool SetNthForm(std::uint32_t a_index, TESForm* a_form);
		bool RemoveNthForm(std::uint32_t a_index);

		[[nodiscard]] TESForm* GetNthEditorForm(std::uint32_t a_index) const;
		bool SetNthEditorForm(std::uint32_t a_index, TESForm* a_form);
		bool RemoveNthEditorForm(std::uint32_t a_index);

		[[nodiscard]] TESForm* GetNthScriptForm(std::uint32_t a_index) const;
		bool SetNthScriptForm(std::uint32_t a_index, TESForm* a_form);
		bool RemoveNthScriptForm(std::uint32_t a_index);

		bool AddEditorForm(TESForm* a_form);
		bool RemoveEditorForm(const TESForm* a_form);

		bool AddScriptForm(TESForm* a_form);
		bool RemoveScriptForm(const TESForm* a_form);

		void AddEditorForms(std::span<TESForm*> a_forms);
		void RemoveEditorForms(std::span<TESForm*> a_forms);

		void AddScriptForms(std::span<TESForm*> a_forms);
		void RemoveScriptForms(std::span<TESForm*> a_forms);

		void ClearForms();
		void ClearEditorForms();
		void ClearScriptForms();

		BSContainer::ForEachResult ForEachForm(
			const REX::NotNull<std::function<BSContainer::ForEachResult(TESForm*)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachEditorForm(
			const REX::NotNull<std::function<BSContainer::ForEachResult(TESForm*)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachScriptForm(
			const REX::NotNull<std::function<BSContainer::ForEachResult(TESForm*)>>& a_predicate) const;

		// members
		BSTArray<TESForm*> arrayOfForms;		   // 20
		BSTArray<TESFormID>* scriptAddedTempForms; // 38
		std::uint32_t scriptAddedFormCount;		   // 40
	};
	static_assert(sizeof(BGSListForm) == 0x48);
}

#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSListForm : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSListForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSListForm;
		inline static constexpr auto FORM_TYPE = FormType::FormList;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				AddedForm = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]]
		auto GetFormCount() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetEditorFormCount() const noexcept -> std::uint32_t;
		[[nodiscard]]
		auto GetScriptFormCount() const noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetAllForms() const -> BSTArray<TESForm*>;

		[[nodiscard]]
		auto GetScriptForms() const -> std::optional<BSTArray<TESForm*>>;
		void SetScriptForms(std::span<TESForm*> a_forms);

		[[nodiscard]]
		auto ContainsForm(const TESForm* a_form) const -> bool;
		[[nodiscard]]
		auto ContainsEditorForm(const TESForm* a_form) const -> bool;
		[[nodiscard]]
		auto ContainsScriptForm(const TESForm* a_form) const -> bool;

		[[nodiscard]]
		auto GetFormIndex(const TESForm* a_form) const -> std::optional<std::uint32_t>;
		[[nodiscard]]
		auto GetEditorFormIndex(const TESForm* a_form) const -> std::optional<std::uint32_t>;
		[[nodiscard]]
		auto GetScriptFormIndex(const TESForm* a_form) const -> std::optional<std::uint32_t>;

		[[nodiscard]]
		auto GetNthForm(std::uint32_t a_index) const -> TESForm*;
		auto SetNthForm(std::uint32_t a_index, TESForm* a_form) -> bool;
		auto RemoveNthForm(std::uint32_t a_index) -> bool;

		[[nodiscard]]
		auto GetNthEditorForm(std::uint32_t a_index) const -> TESForm*;
		auto SetNthEditorForm(std::uint32_t a_index, TESForm* a_form) -> bool;
		auto RemoveNthEditorForm(std::uint32_t a_index) -> bool;

		[[nodiscard]]
		auto GetNthScriptForm(std::uint32_t a_index) const -> TESForm*;
		auto SetNthScriptForm(std::uint32_t a_index, TESForm* a_form) -> bool;
		auto RemoveNthScriptForm(std::uint32_t a_index) -> bool;

		auto AddEditorForm(TESForm* a_form) -> bool;
		auto RemoveEditorForm(const TESForm* a_form) -> bool;

		auto AddScriptForm(TESForm* a_form) -> bool;
		auto RemoveScriptForm(const TESForm* a_form) -> bool;

		void AddEditorForms(std::span<TESForm*> a_forms);
		void RemoveEditorForms(std::span<TESForm*> a_forms);

		void AddScriptForms(std::span<TESForm*> a_forms);
		void RemoveScriptForms(std::span<TESForm*> a_forms);

		void ClearForms();
		void ClearEditorForms();
		void ClearScriptForms();

		auto ForEachForm(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESForm*) const>>& a_predicate) const
			-> BSContainer::ForEachResult;
		auto ForEachEditorForm(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESForm*) const>>& a_predicate) const
			-> BSContainer::ForEachResult;
		auto ForEachScriptForm(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESForm*) const>>& a_predicate) const
			-> BSContainer::ForEachResult;

		// members
		BSTArray<TESForm*> arrayOfForms;		   // 0x20
		BSTArray<TESFormID>* scriptAddedTempForms; // 0x38
		std::uint32_t scriptAddedFormCount;		   // 0x40
	};

	static_assert(sizeof(BGSListForm) == 0x48);
}

#include "RE/B/BGSListForm.hpp"

#include "RE/B/BSReadWriteLock.hpp"

namespace RE
{
	auto BGSListForm::GetFormCount() const noexcept -> std::uint32_t
	{
		return GetEditorFormCount() + GetScriptFormCount();
	}

	auto BGSListForm::GetEditorFormCount() const noexcept -> std::uint32_t
	{
		return arrayOfForms.size();
	}

	auto BGSListForm::GetScriptFormCount() const noexcept -> std::uint32_t
	{
		return scriptAddedFormCount;
	}

	auto BGSListForm::GetAllForms() const -> BSTArray<TESForm*>
	{
		auto result = BSTArray<TESForm*>();
		result.reserve(GetFormCount());

		ForEachForm([&result](TESForm* a_form) -> BSContainer::ForEachResult {
			result.push_back(a_form);
			return BSContainer::ForEachResult::Continue;
		});

		return result;
	}

	auto BGSListForm::GetScriptForms() const -> std::optional<BSTArray<TESForm*>>
	{
		auto result = BSTArray<TESForm*>();
		result.reserve(GetScriptFormCount());

		ForEachScriptForm([&result](TESForm* a_form) -> BSContainer::ForEachResult {
			result.push_back(a_form);
			return BSContainer::ForEachResult::Continue;
		});

		return result;
	}

	void BGSListForm::SetScriptForms(std::span<TESForm*> a_forms)
	{
		const auto count = static_cast<std::uint32_t>(a_forms.size());
		if (count == 0) {
			ClearScriptForms();
			return;
		}

		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			scriptForms = new BSTArray<TESFormID>();
		}

		scriptForms->clear();
		scriptForms->reserve(count);

		for (const auto* form : a_forms) {
			if (form) {
				scriptForms->push_back(form->GetFormID());
			}
		}

		scriptAddedFormCount = scriptForms->size();

		AddChange(ChangeFlags::AddedForm);
	}

	auto BGSListForm::ContainsForm(const TESForm* a_form) const -> bool
	{
		return ContainsEditorForm(a_form) || ContainsScriptForm(a_form);
	}

	auto BGSListForm::ContainsEditorForm(const TESForm* a_form) const -> bool
	{
		return std::ranges::contains(arrayOfForms, a_form);
	}

	auto BGSListForm::ContainsScriptForm(const TESForm* a_form) const -> bool
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		return std::ranges::contains(*scriptForms, a_form ? a_form->GetFormID() : 0);
	}

	auto BGSListForm::GetFormIndex(const TESForm* a_form) const -> std::optional<std::uint32_t>
	{
		const auto editorIndex = GetEditorFormIndex(a_form);
		if (editorIndex.has_value()) {
			return editorIndex;
		}

		const auto scriptIndex = GetScriptFormIndex(a_form);
		if (scriptIndex.has_value()) {
			return scriptIndex.value() + GetEditorFormCount();
		}

		return std::nullopt;
	}

	auto BGSListForm::GetEditorFormIndex(const TESForm* a_form) const -> std::optional<std::uint32_t>
	{
		const auto* formIt = std::ranges::find(arrayOfForms, a_form);
		if (formIt == arrayOfForms.end()) {
			return std::nullopt;
		}

		return static_cast<std::uint32_t>(std::distance(arrayOfForms.begin(), formIt));
	}

	auto BGSListForm::GetScriptFormIndex(const TESForm* a_form) const -> std::optional<std::uint32_t>
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return std::nullopt;
		}

		const auto* formIt = std::ranges::find(*scriptForms, a_form ? a_form->GetFormID() : 0);
		if (formIt == scriptForms->end()) {
			return std::nullopt;
		}

		return static_cast<std::uint32_t>(std::distance(scriptForms->begin(), formIt));
	}

	auto BGSListForm::GetNthForm(std::uint32_t a_index) const -> TESForm*
	{
		const auto editorCount = GetEditorFormCount();
		if (a_index < editorCount) {
			return GetNthEditorForm(a_index);
		}

		return GetNthScriptForm(a_index - editorCount);
	}

	auto BGSListForm::SetNthForm(std::uint32_t a_index, TESForm* a_form) -> bool
	{
		if (!a_form) {
			return false;
		}

		const auto editorCount = GetEditorFormCount();
		if (a_index < editorCount) {
			return SetNthEditorForm(a_index, a_form);
		}

		return SetNthScriptForm(a_index - editorCount, a_form);
	}

	auto BGSListForm::RemoveNthForm(std::uint32_t a_index) -> bool
	{
		const auto editorCount = GetEditorFormCount();
		if (a_index < editorCount) {
			return RemoveNthEditorForm(a_index);
		}

		return RemoveNthScriptForm(a_index - editorCount);
	}

	auto BGSListForm::GetNthEditorForm(std::uint32_t a_index) const -> TESForm*
	{
		return a_index < arrayOfForms.size() ? arrayOfForms[a_index] : nullptr;
	}

	auto BGSListForm::SetNthEditorForm(std::uint32_t a_index, TESForm* a_form) -> bool
	{
		if (!a_form) {
			return false;
		}

		if (a_index >= arrayOfForms.size() || ContainsForm(a_form)) {
			return false;
		}

		arrayOfForms[a_index] = a_form;
		return true;
	}

	auto BGSListForm::RemoveNthEditorForm(std::uint32_t a_index) -> bool
	{
		if (a_index >= arrayOfForms.size()) {
			return false;
		}

		arrayOfForms.erase(arrayOfForms.begin() + a_index);
		return true;
	}

	auto BGSListForm::GetNthScriptForm(std::uint32_t a_index) const -> TESForm*
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return nullptr;
		}

		return a_index < scriptForms->size() ? TESForm::FindFormByNumericID((*scriptForms)[a_index]) : nullptr;
	}

	auto BGSListForm::SetNthScriptForm(std::uint32_t a_index, TESForm* a_form) -> bool
	{
		if (!a_form) {
			return false;
		}

		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		if (a_index >= scriptForms->size() || ContainsForm(a_form)) {
			return false;
		}

		(*scriptForms)[a_index] = a_form->GetFormID();

		AddChange(ChangeFlags::AddedForm);
		return true;
	}

	auto BGSListForm::RemoveNthScriptForm(std::uint32_t a_index) -> bool
	{
		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		if (a_index >= scriptForms->size()) {
			return false;
		}

		scriptForms->erase(scriptForms->begin() + a_index);
		scriptAddedFormCount = scriptForms->size();

		AddChange(ChangeFlags::AddedForm);
		return true;
	}

	auto BGSListForm::AddEditorForm(TESForm* a_form) -> bool
	{
		if (!a_form) {
			return false;
		}

		if (ContainsForm(a_form)) {
			return false;
		}

		arrayOfForms.push_back(a_form);
		return true;
	}

	auto BGSListForm::RemoveEditorForm(const TESForm* a_form) -> bool
	{
		const auto* formIt = std::ranges::find(arrayOfForms, a_form);
		if (formIt == arrayOfForms.end()) {
			return false;
		}

		arrayOfForms.erase(formIt);
		return true;
	}

	auto BGSListForm::AddScriptForm(TESForm* a_form) -> bool
	{
		if (!a_form) {
			return false;
		}

		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			scriptForms = new BSTArray<TESFormID>();
		}
		else if (ContainsScriptForm(a_form)) {
			return false;
		}

		scriptForms->push_back(a_form->GetFormID());
		scriptAddedFormCount = scriptForms->size();

		AddChange(ChangeFlags::AddedForm);
		return true;
	}

	auto BGSListForm::RemoveScriptForm(const TESForm* a_form) -> bool
	{
		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		const auto* formIt = std::ranges::find(*scriptForms, a_form ? a_form->GetFormID() : 0);
		if (formIt == scriptForms->end()) {
			return false;
		}

		scriptForms->erase(formIt);
		scriptAddedFormCount = scriptForms->size();

		AddChange(ChangeFlags::AddedForm);
		return true;
	}

	void BGSListForm::AddEditorForms(std::span<TESForm*> a_forms)
	{
		arrayOfForms.reserve(arrayOfForms.size() + static_cast<std::uint32_t>(a_forms.size()));

		for (auto* form : a_forms) {
			if (form && !ContainsForm(form)) {
				arrayOfForms.push_back(form);
			}
		}
	}

	void BGSListForm::RemoveEditorForms(std::span<TESForm*> a_forms)
	{
		for (auto* form : a_forms) {
			const auto* formIt = std::ranges::find(arrayOfForms, form);
			if (formIt != arrayOfForms.end()) {
				arrayOfForms.erase(formIt);
			}
		}
	}

	void BGSListForm::AddScriptForms(std::span<TESForm*> a_forms)
	{
		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			scriptForms = new BSTArray<TESFormID>();
		}

		scriptForms->reserve(scriptForms->size() + static_cast<std::uint32_t>(a_forms.size()));

		for (const auto* form : a_forms) {
			if (form && !ContainsForm(form)) {
				scriptForms->push_back(form->GetFormID());
			}
		}

		scriptAddedFormCount = scriptForms->size();

		AddChange(ChangeFlags::AddedForm);
	}

	void BGSListForm::RemoveScriptForms(std::span<TESForm*> a_forms)
	{
		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return;
		}

		for (const auto* form : a_forms) {
			if (!form) {
				continue;
			}

			const auto* formIt = std::ranges::find(*scriptForms, form->GetFormID());
			if (formIt != scriptForms->end()) {
				scriptForms->erase(formIt);
			}
		}

		scriptAddedFormCount = static_cast<std::uint32_t>(scriptForms->size());

		AddChange(ChangeFlags::AddedForm);
	}

	void BGSListForm::ClearForms()
	{
		ClearEditorForms();
		ClearScriptForms();
	}

	void BGSListForm::ClearEditorForms()
	{
		arrayOfForms.clear();
	}

	void BGSListForm::ClearScriptForms()
	{
		if (scriptAddedTempForms) {
			delete scriptAddedTempForms;
			scriptAddedTempForms = nullptr;
		}

		scriptAddedFormCount = 0;

		AddChange(ChangeFlags::AddedForm);
	}

	auto BGSListForm::ForEachForm(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESForm*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		if (ForEachEditorForm(a_predicate) == BSContainer::ForEachResult::Stop) {
			return BSContainer::ForEachResult::Stop;
		}

		if (ForEachScriptForm(a_predicate) == BSContainer::ForEachResult::Stop) {
			return BSContainer::ForEachResult::Stop;
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto BGSListForm::ForEachEditorForm(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESForm*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		for (auto* form : arrayOfForms) {
			if (std::invoke(a_predicate.get(), form) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto BGSListForm::ForEachScriptForm(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESForm*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto&& [formIDMap, formIDMutex] = TESForm::GetAllFormsByNumericID();
		if (!formIDMap) {
			return BSContainer::ForEachResult::Continue;
		}

		const auto formIDLock = BSAutoReadLock(formIDMutex.get());

		for (const auto formIDElem : *scriptForms) {
			const auto formIt = formIDMap->find(formIDElem);
			if (formIt == formIDMap->end()) {
				continue;
			}

			auto* form = formIt->second;
			if (std::invoke(a_predicate.get(), form) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}

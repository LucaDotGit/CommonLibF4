#include "RE/B/BGSListForm.hpp"

namespace RE
{
	std::uint32_t BGSListForm::GetFormCount() const noexcept
	{
		return GetEditorFormCount() + GetScriptFormCount();
	}

	std::uint32_t BGSListForm::GetEditorFormCount() const noexcept
	{
		return arrayOfForms.size();
	}

	std::uint32_t BGSListForm::GetScriptFormCount() const noexcept
	{
		return scriptAddedFormCount;
	}

	std::vector<TESForm*> BGSListForm::GetAllForms() const
	{
		auto result = std::vector<TESForm*>();
		result.reserve(GetFormCount());

		ForEachForm([&result](TESForm* a_form) -> BSContainer::ForEachResult {
			result.push_back(a_form);
			return BSContainer::ForEachResult::kContinue;
		});

		return result;
	}

	auto BGSListForm::GetScriptForms() const
		-> std::optional<std::vector<TESForm*>>
	{
		auto result = std::vector<TESForm*>();
		result.reserve(GetScriptFormCount());

		ForEachScriptForm([&result](TESForm* a_form) -> BSContainer::ForEachResult {
			result.push_back(a_form);
			return BSContainer::ForEachResult::kContinue;
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

		scriptAddedFormCount = count;

		AddChange(ChangeFlags::kAddedForm);
	}

	bool BGSListForm::ContainsForm(const TESForm* a_form) const
	{
		return ContainsEditorForm(a_form) || ContainsScriptForm(a_form);
	}

	bool BGSListForm::ContainsEditorForm(const TESForm* a_form) const
	{
		return std::ranges::contains(arrayOfForms, a_form);
	}

	bool BGSListForm::ContainsScriptForm(const TESForm* a_form) const
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return false;
		}

		return std::ranges::contains(*scriptForms, a_form ? a_form->GetFormID() : 0);
	}

	auto BGSListForm::GetFormIndex(const TESForm* a_form) const
		-> std::optional<std::uint32_t>
	{
		const auto editorIndex = GetEditorFormIndex(a_form);
		if (editorIndex) {
			return *editorIndex;
		}

		const auto scriptIndex = GetScriptFormIndex(a_form);
		if (scriptIndex) {
			return *scriptIndex + GetEditorFormCount();
		}

		return std::nullopt;
	}

	auto BGSListForm::GetEditorFormIndex(const TESForm* a_form) const
		-> std::optional<std::uint32_t>
	{
		const auto* formIt = std::ranges::find(arrayOfForms, a_form);
		if (formIt == arrayOfForms.end()) {
			return std::nullopt;
		}

		return static_cast<std::uint32_t>(std::distance(arrayOfForms.begin(), formIt));
	}

	auto BGSListForm::GetScriptFormIndex(const TESForm* a_form) const
		-> std::optional<std::uint32_t>
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

	TESForm* BGSListForm::GetNthForm(std::uint32_t a_index) const
	{
		const auto editorCount = GetEditorFormCount();
		if (a_index < editorCount) {
			return GetNthEditorForm(a_index);
		}

		return GetNthScriptForm(a_index - editorCount);
	}

	bool BGSListForm::SetNthForm(std::uint32_t a_index, TESForm* a_form)
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

	bool BGSListForm::RemoveNthForm(std::uint32_t a_index)
	{
		const auto editorCount = GetEditorFormCount();
		if (a_index < editorCount) {
			return RemoveNthEditorForm(a_index);
		}

		return RemoveNthScriptForm(a_index - editorCount);
	}

	TESForm* BGSListForm::GetNthEditorForm(std::uint32_t a_index) const
	{
		return a_index < arrayOfForms.size() ? arrayOfForms[a_index] : nullptr;
	}

	bool BGSListForm::SetNthEditorForm(std::uint32_t a_index, TESForm* a_form)
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

	bool BGSListForm::RemoveNthEditorForm(std::uint32_t a_index)
	{
		if (a_index >= arrayOfForms.size()) {
			return false;
		}

		arrayOfForms.erase(arrayOfForms.begin() + a_index);
		return true;
	}

	TESForm* BGSListForm::GetNthScriptForm(std::uint32_t a_index) const
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return nullptr;
		}

		return a_index < scriptForms->size() ? TESForm::FindFormByNumericID((*scriptForms)[a_index]) : nullptr;
	}

	bool BGSListForm::SetNthScriptForm(std::uint32_t a_index, TESForm* a_form)
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

		AddChange(ChangeFlags::kAddedForm);
		return true;
	}

	bool BGSListForm::RemoveNthScriptForm(std::uint32_t a_index)
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

		AddChange(ChangeFlags::kAddedForm);
		return true;
	}

	bool BGSListForm::AddEditorForm(TESForm* a_form)
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

	bool BGSListForm::RemoveEditorForm(const TESForm* a_form)
	{
		const auto* formIt = std::ranges::find(arrayOfForms, a_form);
		if (formIt == arrayOfForms.end()) {
			return false;
		}

		arrayOfForms.erase(formIt);
		return true;
	}

	bool BGSListForm::AddScriptForm(TESForm* a_form)
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

		AddChange(ChangeFlags::kAddedForm);
		return true;
	}

	bool BGSListForm::RemoveScriptForm(const TESForm* a_form)
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

		AddChange(ChangeFlags::kAddedForm);
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

		for (auto* form : a_forms) {
			if (form && !ContainsForm(form)) {
				scriptForms->push_back(form->GetFormID());
			}
		}

		scriptAddedFormCount = scriptForms->size();

		AddChange(ChangeFlags::kAddedForm);
	}

	void BGSListForm::RemoveScriptForms(std::span<TESForm*> a_forms)
	{
		auto*& scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return;
		}

		for (auto* form : a_forms) {
			if (!form) {
				continue;
			}

			const auto* formIt = std::ranges::find(*scriptForms, form->GetFormID());
			if (formIt != scriptForms->end()) {
				scriptForms->erase(formIt);
			}
		}

		scriptAddedFormCount = static_cast<std::uint32_t>(scriptForms->size());

		AddChange(ChangeFlags::kAddedForm);
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

		AddChange(ChangeFlags::kAddedForm);
	}

	BSContainer::ForEachResult BGSListForm::ForEachForm(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESForm*)>>& a_predicate) const
	{
		if (ForEachEditorForm(a_predicate) == BSContainer::ForEachResult::kStop) {
			return BSContainer::ForEachResult::kStop;
		}

		if (ForEachScriptForm(a_predicate) == BSContainer::ForEachResult::kStop) {
			return BSContainer::ForEachResult::kStop;
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult BGSListForm::ForEachEditorForm(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESForm*)>>& a_predicate) const
	{
		for (auto* form : arrayOfForms) {
			if (std::invoke(*a_predicate, form) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult BGSListForm::ForEachScriptForm(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESForm*)>>& a_predicate) const
	{
		const auto* scriptForms = scriptAddedTempForms;
		if (!scriptForms) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto [formIDMap, formIDMutex] = TESForm::GetAllFormsByNumericID();
		if (!formIDMap) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto formIDLock = BSAutoReadLock(formIDMutex);

		for (const auto formIDElem : *scriptForms) {
			const auto formIt = formIDMap->find(formIDElem);
			if (formIt != formIDMap->end()) {
				continue;
			}

			auto* form = formIt->second;
			if (std::invoke(*a_predicate, form) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}

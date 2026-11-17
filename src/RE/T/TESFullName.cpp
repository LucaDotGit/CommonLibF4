#include "RE/T/TESFullName.hpp"

#include "RE/T/TESActorBase.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESObjectCELL.hpp"
#include "RE/T/TESObjectREFR.hpp"

namespace RE
{
	// Suppress linker warning from the destructor of `MapMarkerData`.
	TESFullName::~TESFullName() = default;

	auto TESFullName::GetSparseFullNameMap() noexcept -> BSTHashMap<const TESForm*, BGSLocalizedString>&
	{
		static const auto SPARSE_FULL_NAME_MAP = REL::Relocation<BSTHashMap<const TESForm*, BGSLocalizedString>*>{
			ID::TESFullName::SparseFullNameMap,
			Offset::TESFullName::SparseFullNameMap
		};
		return *SPARSE_FULL_NAME_MAP;
	}

	auto TESFullName::GetFormFullName(const TESForm* a_form) -> std::optional<BGSLocalizedString>
	{
		const auto* nameForm = DynamicCast<const TESFullName*>(a_form);
		if (nameForm) {
			return nameForm->fullName;
		}

		const auto& fullNameMap = GetSparseFullNameMap();

		const auto fullNameIt = fullNameMap.find(a_form);
		if (fullNameIt != fullNameMap.end()) {
			return fullNameIt->second;
		}

		return std::nullopt;
	}

	auto TESFullName::SetFormFullName(TESForm* a_form, const BGSLocalizedString& a_fullName) -> bool
	{
		auto* nameForm = DynamicCast<TESFullName*>(a_form);
		if (!nameForm) {
			return false;
		}

		nameForm->fullName = a_fullName;

		{
			auto* actorBase = DynamicCast<TESActorBase*>(a_form);
			if (actorBase) {
				actorBase->AddChange(TESActorBase::ChangeFlags::FullName);
				return true;
			}
		}

		{
			auto* cell = DynamicCast<TESObjectCELL*>(a_form);
			if (cell) {
				cell->AddChange(TESObjectCELL::ChangeFlags::FullName);
				return true;
			}
		}

		a_form->AddChange(TESBoundObject::ChangeFlags::FullName);
		return true;
	}

	auto TESFullName::GetFormFullOrDisplayName(const TESForm* a_form) -> std::optional<BGSLocalizedString>
	{
		auto fullName = GetFormFullName(a_form);
		if (fullName.has_value()) {
			return fullName;
		}

		const auto* ref = DynamicCast<const TESObjectREFR*>(a_form);
		if (!ref) {
			return std::nullopt;
		}

		return ref->GetDisplayName();
	}

	auto TESFullName::SetFormFullOrDisplayName(TESForm* a_form, const BGSLocalizedString& a_name) -> bool
	{
		if (SetFormFullName(a_form, a_name)) {
			return true;
		}

		auto* ref = DynamicCast<TESObjectREFR*>(a_form);
		if (!ref) {
			return false;
		}

		return ref->SetDisplayName(a_name);
	}
}

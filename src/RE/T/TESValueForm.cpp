#include "RE/T/TESValueForm.hpp"

#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESObjectARMO.hpp"
#include "RE/T/TESObjectWEAP.hpp"

namespace RE
{
	auto TESValueForm::GetFormValue(const TESForm* a_form) -> std::optional<std::int32_t>
	{
		if (!a_form) {
			return std::nullopt;
		}

		{
			const auto* armor = DynamicCast<const TESObjectARMO*>(a_form);
			if (armor) {
				return armor->armorData.value;
			}
		}

		{
			const auto* weapon = DynamicCast<const TESObjectWEAP*>(a_form);
			if (weapon) {
				return weapon->weaponData.value;
			}
		}

		{
			const auto* valueHolder = DynamicCast<const TESValueForm*>(a_form);
			if (valueHolder) {
				return valueHolder->value;
			}
		}

		return std::nullopt;
	}

	auto TESValueForm::SetFormValue(TESForm* a_form, std::int32_t a_value) -> bool
	{
		if (!a_form) {
			return false;
		}

		{
			auto* armor = DynamicCast<TESObjectARMO*>(a_form);
			if (armor) {
				armor->armorData.value = static_cast<std::uint32_t>(a_value);
				armor->AddChange(TESObjectARMO::ChangeFlags::Value);
				return true;
			}
		}

		{
			auto* weapon = DynamicCast<TESObjectWEAP*>(a_form);
			if (weapon) {
				weapon->weaponData.value = static_cast<std::uint32_t>(a_value);
				weapon->AddChange(TESObjectWEAP::ChangeFlags::Value);
				return true;
			}
		}

		{
			auto* valueHolder = DynamicCast<TESValueForm*>(a_form);
			if (valueHolder) {
				valueHolder->value = a_value;
				a_form->AddChange(TESBoundObject::ChangeFlags::Value);
				return true;
			}
		}

		return false;
	}
}

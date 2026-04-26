#include "RE/T/TESWeightForm.hpp"

#include "RE/T/TESForm.hpp"
#include "RE/T/TESObjectARMO.hpp"
#include "RE/T/TESObjectWEAP.hpp"

namespace RE
{
	auto TESWeightForm::GetFormWeight(const TESForm* a_form) -> std::optional<REX::Float32>
	{
		if (!a_form) {
			return std::nullopt;
		}

		const auto* armor = DynamicCast<const TESObjectARMO*>(a_form);
		if (armor) {
			return armor->armorData.weight;
		}

		const auto* weapon = DynamicCast<const TESObjectWEAP*>(a_form);
		if (weapon) {
			return weapon->weaponData.weight;
		}

		const auto* weightHolder = DynamicCast<const TESWeightForm*>(a_form);
		if (weightHolder) {
			return weightHolder->weight;
		}

		return std::nullopt;
	}

	bool TESWeightForm::SetFormWeight(TESForm* a_form, REX::Float32 a_weight)
	{
		if (!a_form) {
			return false;
		}

		auto* armor = DynamicCast<TESObjectARMO*>(a_form);
		if (armor) {
			armor->armorData.weight = a_weight;
			return true;
		}

		auto* weapon = DynamicCast<TESObjectWEAP*>(a_form);
		if (weapon) {
			weapon->weaponData.weight = a_weight;
			return true;
		}

		auto* weightHolder = DynamicCast<TESWeightForm*>(a_form);
		if (weightHolder) {
			weightHolder->weight = a_weight;
			return true;
		}

		return false;
	}
}

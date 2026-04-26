#include "RE/T/TESHealthForm.hpp"

#include "RE/T/TESForm.hpp"
#include "RE/T/TESObjectARMO.hpp"

namespace RE
{
	auto TESHealthForm::GetFormHealth(const TESForm* a_form) -> std::optional<std::uint32_t>
	{
		if (!a_form) {
			return std::nullopt;
		}

		const auto* armor = DynamicCast<const TESObjectARMO*>(a_form);
		if (armor) {
			return armor->armorData.health;
		}

		const auto* healthHolder = DynamicCast<const TESHealthForm*>(a_form);
		if (healthHolder) {
			return healthHolder->health;
		}

		return std::nullopt;
	}

	bool TESHealthForm::SetFormHealth(TESForm* a_form, std::uint32_t a_health)
	{
		if (!a_form) {
			return false;
		}

		auto* armor = DynamicCast<TESObjectARMO*>(a_form);
		if (armor) {
			armor->armorData.health = a_health;
			return true;
		}

		auto* healthHolder = DynamicCast<TESHealthForm*>(a_form);
		if (healthHolder) {
			healthHolder->health = a_health;
			return true;
		}

		return false;
	}
}

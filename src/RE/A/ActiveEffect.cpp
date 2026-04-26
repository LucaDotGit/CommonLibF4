#include "RE/A/ActiveEffect.hpp"

#include "RE/A/Actor.hpp"
#include "RE/M/MagicTarget.hpp"

namespace RE
{
	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	FormType ActiveEffect::GetFormType() const noexcept
	{
		return FORM_TYPE;
	}

	bool ActiveEffect::CheckDisplacementSpellOnTarget()
	{
		using FuncType = decltype(&ActiveEffect::CheckDisplacementSpellOnTarget);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ActiveEffect::CheckDisplacementSpellOnTarget };
		return std::invoke(FUNC, this);
	}

	NiPointer<Actor> ActiveEffect::GetTargetActor() const
	{
		if (!target) {
			return nullptr;
		}

		if (!target->MagicTargetIsActor()) {
			return nullptr;
		}

		auto* actor = DynamicCast<Actor*>(target);
		if (!actor) {
			return nullptr;
		}

		return NiPointer(actor);
	}
}

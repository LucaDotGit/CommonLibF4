#include "RE/A/ActiveEffect.hpp"

#include "RE/A/Actor.hpp"
#include "RE/M/MagicTarget.hpp"

namespace RE
{
	// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
	auto ActiveEffect::GetFormType() const noexcept -> FormType
	{
		return FORM_TYPE;
	}

	auto ActiveEffect::CheckDisplacementSpellOnTarget() -> bool
	{
		using FuncType = decltype(&ActiveEffect::CheckDisplacementSpellOnTarget);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ActiveEffect::CheckDisplacementSpellOnTarget);
		return std::invoke(FUNC, this);
	}

	auto ActiveEffect::GetTargetActor() const -> NiPointer<Actor>
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

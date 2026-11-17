#include "RE/M/MagicTarget.hpp"

#include "RE/A/ActiveEffect.hpp"
#include "RE/A/ActiveEffectList.hpp"

namespace RE
{
	auto MagicTarget::IsTakingHealthDamageFromActiveEffect() const -> bool
	{
		using FuncType = decltype(&MagicTarget::IsTakingHealthDamageFromActiveEffect);
		static const auto FUNC = REL::Relocation<FuncType>(ID::MagicTarget::IsTakingHealthDamageFromActiveEffect);
		return std::invoke(FUNC, this);
	}

	auto MagicTarget::IsTakingRadDamageFromActiveEffect() const -> bool
	{
		using FuncType = decltype(&MagicTarget::IsTakingRadDamageFromActiveEffect);
		static const auto FUNC = REL::Relocation<FuncType>(ID::MagicTarget::IsTakingRadDamageFromActiveEffect);
		return std::invoke(FUNC, this);
	}

	auto MagicTarget::GetActiveEffectByID(std::uint16_t a_id) const -> BSTSmartPointer<ActiveEffect>
	{
		const auto* activeEffectList = const_cast<MagicTarget*>(this)->GetActiveEffectList();
		if (!activeEffectList) {
			return nullptr;
		}

		return activeEffectList->GetActiveEffectByID(a_id);
	}
}
